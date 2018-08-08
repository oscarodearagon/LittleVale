/*
 * minigauss.c
 *
 * Created: 8/7/2018 7:50:16 PM
 *  Author: SirOscarin
 */ 

#include <minigauss.h>
#include <minigauss_cfg.h>
#include <hal_adc_sync.h>
#include <logdebug.h>

extern struct adc_sync_descriptor ADC_0;

static uint8_t au8AdcValues[MINIGAUSS_u8INPUTS_PER_SENSOR*MINIGAUSS_u8SENSOR_QUANTITY]={0}; 

void MINIGAUSS_vInit(void)
{
	adc_sync_enable_channel(&ADC_0, MINIGAUSS_u8ANALOG_INPUT_0);
}

void MINIGAUSS_vReadDevice(void)
{
	uint8_t u8AdcValue = 0;
	adc_sync_read_channel(&ADC_0, MINIGAUSS_u8ANALOG_INPUT_0, &u8AdcValue, 1);
	LOGDEBUG_vSendData(&u8AdcValue, 1);
}

void MINIGAUSS_vGetAdcValues(void)
{
	
}

void MINIGAUSS_vProcess(void)
{
	
}