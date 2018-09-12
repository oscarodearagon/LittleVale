/*
 * rfid.c
 *
 * Created: 9/10/2018 10:13:01 PM
 *  Author: SirOscarin
 */ 

#include <rfid.h>
#include <spiDriver.h>
#include <hal_gpio.h>
#include <string.h>

uint8_t RFID_au8SerNum[RFID_nSERNUM_LENGTH];       // Constante para guardar el numero de serie leido.
uint8_t RFID_au8AserNum[RFID_nSERNUM_LENGTH];      // Constante para guardar el numero d serie de la secion actual.

uint8_t RFID_u8ChipSelectPin;
uint8_t RFID_u8NRSTPD;

bool RFID_boIsCard(void)
{
	uint8_t status;
	uint8_t str[MAX_LEN];
	
	status = RFID_u8MFRC522Request(PICC_REQIDL, str);
	if (status == MI_OK) {
		return true;
		} else {
		return false;
	}
}

bool RFID_boReadCardSerial(void)
{	 
	uint8_t status;
	uint8_t str[MAX_LEN];
	 
	// Anti-colisión, devuelva el número de serie de tarjeta de 4 bytes
	status = RFID_u8Anticoll(str);
	memcpy(RFID_au8SerNum, str, RFID_nSERNUM_LENGTH);
	 
	if (status == MI_OK) {
		return true;
		} else {
		return false;
	}
}


void RFID_vInit(uint8_t u8ChipSelectPin, uint8_t u8NRSTPD)
{
	RFID_u8ChipSelectPin = u8ChipSelectPin;
	RFID_u8NRSTPD = u8NRSTPD;
	
	gpio_set_pin_direction(RFID_u8ChipSelectPin, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(RFID_u8ChipSelectPin, false);
	
	gpio_set_pin_direction(RFID_u8NRSTPD, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(RFID_u8NRSTPD, true);
	
	SPIDRIVER_vInit();
	
	RFID_vReset();
	
	//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
	RFID_vWriteMFRC522(TModeReg, 0x80);   //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	RFID_vWriteMFRC522(TPrescalerReg, 0x3E);  //TModeReg[3..0] + TPrescalerReg
	RFID_vWriteMFRC522(TReloadRegL, 30);
	RFID_vWriteMFRC522(TReloadRegH, 0);
	
	RFID_vWriteMFRC522(TxAutoReg, 0x40);    //100%ASK
	RFID_vWriteMFRC522(ModeReg, 0x3D);    // CRC valor inicial de 0x6363

	//ClearBitMask(Status2Reg, 0x08); //MFCrypto1On=0
	//writeMFRC522(RxSelReg, 0x86);   //RxWait = RxSelReg[5..0]
	RFID_vWriteMFRC522(RFCfgReg, 0x7F);     //RxGain = 48dB

	RFID_vAntennaOn();    //Abre  la antena
}

void RFID_vReset(void)
{
	RFID_vWriteMFRC522(CommandReg, PCD_RESETPHASE);
}

void RFID_vWriteMFRC522(uint8_t addr, uint8_t val)
{
	uint8_t u8TxData = 0;
	uint8_t u8RxData = 0;
	gpio_set_pin_level(RFID_u8ChipSelectPin, false);

	//0XXXXXX0 formato de dirección
	u8TxData = (addr<<1)&0x7E;
	(void) SPIDRIVER_i32TransferByte(u8TxData, &u8RxData);
	u8TxData = val;
	(void) SPIDRIVER_i32TransferByte(val, &u8RxData);
	
	gpio_set_pin_level(RFID_u8ChipSelectPin, true);
}

void RFID_vAntennaOn(void)
{
	uint8_t temp;

	temp = RFID_u8ReadMFRC522(TxControlReg);
	if (!(temp & 0x03))
	{
		RFID_vSetBitMask(TxControlReg, 0x03);
	}
}

/*
 *  Read_MFRC522 Nombre de la función: Read_MFRC522
 *  Descripción: Desde el MFRC522 leer un byte de un registro de datos
 *  Los parámetros de entrada: addr - la dirección de registro
 *  Valor de retorno: Devuelve un byte de datos de lectura
 */
uint8_t RFID_u8ReadMFRC522(uint8_t addr)
{
  uint8_t u8TxData = 0;
  uint8_t u8RxData = 0;
  int32_t i32Status = 0;
  
  gpio_set_pin_level(RFID_u8ChipSelectPin, false);
  u8TxData = ((addr<<1)&0x7E) | 0x80;
  (void) SPIDRIVER_i32TransferByte(u8TxData, &u8RxData);
  u8TxData = 0x00;  
  i32Status = SPIDRIVER_i32TransferByte(u8TxData, &u8RxData);
  gpio_set_pin_level(RFID_u8ChipSelectPin, true);
  
  if(0 > i32Status)
  {
	  //Error
	  u8RxData = 0;
  }
  
  return u8RxData; 
}

void RFID_vSetBitMask(uint8_t reg, uint8_t mask)  
{ 
    uint8_t tmp;
    tmp = RFID_u8ReadMFRC522(reg);
    RFID_vWriteMFRC522(reg, tmp | mask);  // set bit mask
}

void RFID_vClearBitMask(uint8_t reg, uint8_t mask)
{
    uint8_t tmp;
    tmp = RFID_u8ReadMFRC522(reg);
    RFID_vWriteMFRC522(reg, tmp & (~mask));  // clear bit mask
} 

void RFID_vCalculateCRC(uint8_t *pIndata, uint8_t len, uint8_t *pOutData)
{
    uint8_t i, n;

    RFID_vClearBitMask(DivIrqReg, 0x04);      //CRCIrq = 0
    RFID_vSetBitMask(FIFOLevelReg, 0x80);     //Claro puntero FIFO
    //Write_MFRC522(CommandReg, PCD_IDLE);

  //Escribir datos en el FIFO 
    for (i=0; i<len; i++)
    {   
		RFID_vWriteMFRC522(FIFODataReg, *(pIndata+i));   
	}
    RFID_vWriteMFRC522(CommandReg, PCD_CALCCRC);

  // Esperar a la finalización de cálculo del CRC
    i = 0xFF;
    do 
    {
        n = RFID_u8ReadMFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));      //CRCIrq = 1

  //Lea el cálculo de CRC
    pOutData[0] = RFID_u8ReadMFRC522(CRCResultRegL);
    pOutData[1] = RFID_u8ReadMFRC522(CRCResultRegM);
}

uint8_t RFID_u8MFRC522ToCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint16_t *backLen)
{
	uint8_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command)
	{
		case PCD_AUTHENT:   // Tarjetas de certificación cerca
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:  //La transmisión de datos FIFO
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
		break;
	}
	
	RFID_vWriteMFRC522(CommIEnReg, irqEn|0x80); //De solicitud de interrupción
	RFID_vClearBitMask(CommIrqReg, 0x80);     // Borrar todos los bits de petición de interrupción
	RFID_vSetBitMask(FIFOLevelReg, 0x80);     //FlushBuffer=1, FIFO de inicialización
	
	RFID_vWriteMFRC522(CommandReg, PCD_IDLE); //NO action;Y cancelar el comando

	//Escribir datos en el FIFO
	for (i=0; i<sendLen; i++)
	{
		RFID_vWriteMFRC522(FIFODataReg, sendData[i]);
	}

	//???? ejecutar el comando
	RFID_vWriteMFRC522(CommandReg, command);
	if (command == PCD_TRANSCEIVE)
	{
		RFID_vSetBitMask(BitFramingReg, 0x80);    //StartSend=1,transmission of data starts
	}
	
	// A la espera de recibir datos para completar
	//i = 2000; //i????????,??M1???????25ms ??? i De acuerdo con el ajuste de frecuencia de reloj, el tiempo máximo de espera operación M1 25ms tarjeta??
	i = 20;
	do
	{
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = RFID_u8ReadMFRC522(CommIrqReg);
		i--;
	}
	while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	RFID_vClearBitMask(BitFramingReg, 0x80);      //StartSend=0
	
	if (i != 0)
	{
		if(!(RFID_u8ReadMFRC522(ErrorReg) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr
		{
			status = MI_OK;
			if (n & irqEn & 0x01)
			{
				status = MI_NOTAGERR;     //??
			}

			if (command == PCD_TRANSCEIVE)
			{
				n = RFID_u8ReadMFRC522(FIFOLevelReg);
				lastBits = RFID_u8ReadMFRC522(ControlReg) & 0x07;
				if (lastBits)
				{
					*backLen = (n-1)*8 + lastBits;
				}
				else
				{
					*backLen = n*8;
				}

				if (n == 0)
				{
					n = 1;
				}
				if (n > MAX_LEN)
				{
					n = MAX_LEN;
				}
				
				//??FIFO??????? Lea los datos recibidos en el FIFO
				for (i=0; i<n; i++)
				{
					backData[i] = RFID_u8ReadMFRC522(FIFODataReg);
				}
			}
		}
		else
		{
			status = MI_ERR;
		}
		
	}
	
	//SetBitMask(ControlReg,0x80);           //timer stops
	//Write_MFRC522(CommandReg, PCD_IDLE);

	return status;
}

/*
 *  Nombre de la función: MFRC522_Request
 *  Descripción: Buscar las cartas, leer el número de tipo de tarjeta
 *  Los parámetros de entrada: reqMode - encontrar el modo de tarjeta,
 *         Tagtype - Devuelve el tipo de tarjeta
 *        0x4400 = Mifare_UltraLight
 *        0x0400 = Mifare_One(S50)
 *        0x0200 = Mifare_One(S70)
 *        0x0800 = Mifare_Pro(X)
 *        0x4403 = Mifare_DESFire
 *  Valor de retorno: el retorno exitoso MI_OK
 */
uint8_t RFID_u8MFRC522Request(uint8_t reqMode, uint8_t *TagType)
{
  uint8_t status;  
  uint16_t backBits;      //   Recibió bits de datos

  RFID_vWriteMFRC522(BitFramingReg, 0x07);    //TxLastBists = BitFramingReg[2..0] ???
  
  TagType[0] = reqMode;
  status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

  if ((status != MI_OK) || (backBits != 0x10))
  {    
    status = MI_ERR;
  }
   
  return status;
}

/**
 *  MFRC522Anticoll -> anticoll
 *  Anti-detección de colisiones, la lectura del número de serie de la tarjeta de tarjeta
 *  @param serNum - devuelve el número de tarjeta 4 bytes de serie, los primeros 5 bytes de bytes de paridad
 *  @return retorno exitoso MI_OK
 */
uint8_t RFID_u8Anticoll(uint8_t *serNum)
{
    uint8_t status;
    uint8_t i;
	uint8_t serNumCheck=0;
    uint16_t unLen;
    

    //ClearBitMask(Status2Reg, 0x08);   //TempSensclear
    //ClearBitMask(CollReg,0x80);     //ValuesAfterColl
	RFID_vWriteMFRC522(BitFramingReg, 0x00);    //TxLastBists = BitFramingReg[2..0]
 
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK)
  {
    //?????? Compruebe el número de serie de la tarjeta
    for (i=0; i<4; i++)
    {   
      serNumCheck ^= serNum[i];
    }
    if (serNumCheck != serNum[i])
    {   
      status = MI_ERR;    
    }
    }

    //SetBitMask(CollReg, 0x80);    //ValuesAfterColl=1

    return status;
}

/* 
 * MFRC522Auth -> auth
 * Verificar la contraseña de la tarjeta
 * Los parámetros de entrada: AuthMode - Modo de autenticación de contraseña
                 0x60 = A 0x60 = validación KeyA
                 0x61 = B 0x61 = validación KeyB
             BlockAddr--  bloque de direcciones
             Sectorkey-- sector contraseña
             serNum--,4? Tarjeta de número de serie, 4 bytes
 * MI_OK Valor de retorno: el retorno exitoso MI_OK
 */
uint8_t RFID_u8Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t *Sectorkey, uint8_t *serNum)
{
    uint8_t status;
    uint16_t recvBits;
    uint8_t i;
	uint8_t buff[12]; 

  //????+???+????+???? Verifique la dirección de comandos de bloques del sector + + contraseña + número de la tarjeta de serie
    buff[0] = authMode;
    buff[1] = BlockAddr;
    for (i=0; i<6; i++)
    {    
    buff[i+2] = *(Sectorkey+i);   
  }
    for (i=0; i<4; i++)
    {    
    buff[i+8] = *(serNum+i);   
  }
    status = RFID_u8MFRC522ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

    if ((status != MI_OK) || (!(RFID_u8ReadMFRC522(Status2Reg) & 0x08)))
    {   
    status = MI_ERR;   
  }
    
    return status;
}

/*
 * MFRC522Read -> read
 * Lectura de datos de bloque
 * Los parámetros de entrada: blockAddr - dirección del bloque; recvData - leer un bloque de datos
 * MI_OK Valor de retorno: el retorno exitoso MI_OK
 */
uint8_t RFID_u8Read(uint8_t blockAddr, uint8_t *recvData)
{
    uint8_t status;
    uint16_t unLen;

    recvData[0] = PICC_READ;
    recvData[1] = blockAddr;
    RFID_vCalculateCRC(recvData,2, &recvData[2]);
    status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

    if ((status != MI_OK) || (unLen != 0x90))
    {
        status = MI_ERR;
    }
    
    return status;
}

/*
 * MFRC522Write -> write
 * La escritura de datos de bloque
 * blockAddr - dirección del bloque; WriteData - para escribir 16 bytes del bloque de datos
 * Valor de retorno: el retorno exitoso MI_OK
 */
uint8_t RFID_u8Write(uint8_t blockAddr, uint8_t *writeData)
{
    uint8_t status;
    uint16_t recvBits;
    uint8_t i;
	uint8_t buff[18]; 
    
    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    RFID_vCalculateCRC(buff, 2, &buff[2]);
    status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {   
    status = MI_ERR;   
  }
        
    if (status == MI_OK)
    {
        for (i=0; i<16; i++)    //?FIFO?16Byte?? Datos a la FIFO 16Byte escribir
        {    
          buff[i] = *(writeData+i);   
        }
        RFID_vCalculateCRC(buff, 16, &buff[16]);
        status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        
    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        {   
      status = MI_ERR;   
    }
    }
    
    return status;
}

/*
 * MFRC522Halt -> halt
 * Cartas de Mando para dormir
 * Los parámetros de entrada: Ninguno
 * Valor devuelto: Ninguno
 */
void RFID_vHalt(void)
{
	uint8_t status;
    uint16_t unLen;
    uint8_t buff[4]; 

    buff[0] = PICC_HALT;
    buff[1] = 0;
    RFID_vCalculateCRC(buff, 2, &buff[2]);
 
    status = RFID_u8MFRC522ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}

void RFID_vGetSerNum(uint8_t *pu8SerNum)
{
	memcpy(pu8SerNum, RFID_au8SerNum, RFID_nSERNUM_LENGTH);
}