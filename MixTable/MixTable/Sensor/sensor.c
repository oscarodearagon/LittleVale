/*
 * sensor.c
 *
 * Created: 8/7/2018 7:51:00 PM
 *  Author: SirOscarin
 */ 

#include <sensor.h>
#include <minigauss.h>
#include <logdebug.h>

static uint8_t SENSOR_au8Values[SENSOR_nCOLUMNS*SENSOR_nROWS] = {0};

void SENSOR_vInit(void)
{
	MINIGAUSS_vInit();
}
	
uint8_t* SENSOR_pu8ReadDevice(void)
{
	MINIGAUSS_vReadDevice(SENSOR_au8Values);
	return SENSOR_au8Values;
}

void SENSOR_vSendValues(void)
{
	uint8_t au8Header[] = {0x00, 0xFF, 0x00};
	uint16_t u16Size = SENSOR_nCOLUMNS*SENSOR_nROWS;
	LOGDEBUG_vSendData(au8Header, 3);
	LOGDEBUG_vSendData(SENSOR_au8Values, u16Size);
}