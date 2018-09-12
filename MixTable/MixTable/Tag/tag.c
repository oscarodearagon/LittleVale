/*
 * tag.c
 *
 * Created: 9/10/2018 10:12:06 PM
 *  Author: SirOscarin
 */ 

#include <tag.h>
#include <rfid.h>

static uint8_t TAG_au8Id[RFID_nSERNUM_LENGTH] = {0};
	
/* Tag Used */
static uint8_t TAG_au8RegisteredIds[TAG_nAVAILABLE_IDS][RFID_nSERNUM_LENGTH] = {
	{0x39, 0x13, 0x3e, 0xae, 0xba},
	{0x99, 0xe1, 0x36, 0xae, 0xe0},
	{0x79, 0x4f, 0x3b, 0xae, 0xa3},
	{0x49, 0x5d, 0x40, 0xae, 0xfa},
	{0x89, 0xd5, 0x46, 0xae, 0xb4}	
};

void TAG_vInit(void)
{
	RFID_vInit(TAG_CHIP_SELECT_PIN, TAG_RESET_PIN);
}

bool TAG_boGetId(uint8_t *pu8Id)
{
	bool boStatus = false;
	uint8_t u8Id = 0;
	
	boStatus = RFID_boIsCard();
	
	if(true == boStatus)
	{
		boStatus = RFID_boReadCardSerial();
		if(true == boStatus)
		{
			RFID_vGetSerNum(TAG_au8Id);
			u8Id = TAG_u8DecodeId();
		}
	}
	RFID_vHalt();
	
	*pu8Id = u8Id;
	return boStatus;
}

uint8_t TAG_u8DecodeId(void)
{
	uint8_t u8SelectedId = 0;
	uint8_t u8Counter = 0;
	bool boValidId = true;
	
	while((true == boValidId) && (RFID_nSERNUM_LENGTH > u8Counter))
	{
		if(TAG_au8RegisteredIds[u8SelectedId][u8Counter] == TAG_au8Id[u8Counter])
		{
			u8Counter++;
		}
		else
		{
			u8Counter = 0;
			u8SelectedId++;
		}
		
		if(u8SelectedId >= TAG_nAVAILABLE_IDS)
		{
			boValidId = false;
		}
	}
	
	if(true == boValidId)
	{
		u8SelectedId++;
	}
	else
	{
		u8SelectedId = 0;
	}
		
	return u8SelectedId;
}