/*
 * minigauss.c
 *
 * Created: 8/7/2018 7:50:16 PM
 *  Author: SirOscarin
 */ 

#include <minigauss.h>
#include <minigauss_cfg.h>
#include <hal_adc_sync.h>
#include <hal_gpio.h>
#include <logdebug.h>

extern struct adc_sync_descriptor ADC_0;

static uint8_t au8AdcValues[MINIGAUSS_u8INPUTS_PER_SENSOR*MINIGAUSS_u8SENSOR_QUANTITY]={0}; 

void MINIGAUSS_vInit(void)
{
	adc_sync_enable_channel(&ADC_0, MINIGAUSS_u8ANALOG_INPUT_0);
	
	/* GPIO init */
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_0, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_1, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_2, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_3, GPIO_DIRECTION_OUT);
	
	gpio_set_pin_pull_mode(MINIGAUSS_u8DIGITAL_OUTPUT_0, GPIO_PULL_UP);
	gpio_set_pin_pull_mode(MINIGAUSS_u8DIGITAL_OUTPUT_1, GPIO_PULL_UP);
	gpio_set_pin_pull_mode(MINIGAUSS_u8DIGITAL_OUTPUT_2, GPIO_PULL_UP);
	gpio_set_pin_pull_mode(MINIGAUSS_u8DIGITAL_OUTPUT_3, GPIO_PULL_UP);
}

void MINIGAUSS_vReadDevice(uint8_t *pu8Storage)
{
	MINIGAUSS_vSaveAdcValues(pu8Storage);
}

void MINIGAUSS_vSaveAdcValues(uint8_t *pu8Storage)
{
	uint8_t u8AdcValue = 0;
	
	for (uint8_t u8Counter=0; MINIGAUSS_u8INPUTS_PER_SENSOR > u8Counter; u8Counter++)
	{
		MINIGAUSS_vSetGpioOutputs(u8Counter);
		
		/* Delay to make output stable */
		MINIGAUSS_vDelay(100);
		
		/* Read ADC value */
		MINIGAUSS_vReadAdcValues(&u8AdcValue);
		
		/* Assign Value to array */
		*(pu8Storage+u8Counter) = u8AdcValue;
	}
}

void MINIGAUSS_vSetGpioOutputs(uint8_t u8Value)
{
	
	if(u8Value & 0x01)
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_3, true);
	}
	else
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_3, false);
	}
	
	if(u8Value & 0x02)
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_2, true);
	}
	else
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_2, false);
	}
	
	if(u8Value & 0x04)
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_1, true);
	}
	else
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_1, false);
	}
	
	if(u8Value & 0x08)
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_0, true);
	}
	else
	{
		gpio_set_pin_level(MINIGAUSS_u8DIGITAL_OUTPUT_0, false);
	}
}

void MINIGAUSS_vDelay(uint8_t u8Loops)
{
	uint32_t u32DummyCounter = 0;
	for(uint8_t u8Counter=0; u8Loops>u8Counter; u8Counter++)
	{
		u32DummyCounter++;
	}
}

void MINIGAUSS_vReadAdcValues(uint8_t *pu8Values)
{
	adc_sync_read_channel(&ADC_0, MINIGAUSS_u8ANALOG_INPUT_0, pu8Values, 1);
	//LOGDEBUG_vSendData(pu8Values, 1);
}

void MINIGAUSS_vAssignAdcValue(uint8_t *pu8AdcRead, uint8_t u8Index)
{
	au8AdcValues[u8Index] = *pu8AdcRead;
}