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
#include <hpl_adc_config.h>
#include <logdebug.h>

extern struct adc_sync_descriptor ADC_0;

void MINIGAUSS_vInit(void)
{
	adc_sync_enable_channel(&ADC_0, MINIGAUSS_u8ANALOG_INPUT_0);
	
	/* GPIO init */
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_0, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_1, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_2, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(MINIGAUSS_u8DIGITAL_OUTPUT_3, GPIO_DIRECTION_OUT);
}

void MINIGAUSS_vReadDevice(uint8_t *pu8Storage)
{
	MINIGAUSS_vSaveAdcValues(pu8Storage);
}

void MINIGAUSS_vSaveAdcValues(uint8_t *pu8Storage)
{
	uint8_t au8AdcValues[MINIGAUSS_u8SENSOR_QUANTITY] = {0};
	uint8_t u8MainOffset = 0;
	uint8_t u8RowOffset = 0;
	
	for (uint8_t u8Counter=0; MINIGAUSS_u8INPUTS_PER_SENSOR > u8Counter; u8Counter++)
	{
		MINIGAUSS_vSetGpioOutputs(u8Counter);
		
		/* Read ADC value */
		MINIGAUSS_vReadAdcValues(au8AdcValues);
		
#if MINIGAUSS_nDEVICE_TYPE == MINIGAUSS_n1x1_TYPE
		u8MainOffset = u8Counter;
		*(pu8Storage+u8MainOffset) = au8AdcValues[MINIGAUSS_u8ANALOG_INPUT_0];
#else
		
		/* Assign Values to array */
		u8MainOffset = u8Counter + u8RowOffset;
		*(pu8Storage+u8MainOffset) = au8AdcValues[MINIGAUSS_u8ANALOG_INPUT_0];
		
		u8MainOffset = u8Counter + u8RowOffset + MINIGAUSS_u8SENSOR_QUANTITY;
		*(pu8Storage+u8MainOffset) = au8AdcValues[MINIGAUSS_u8ANALOG_INPUT_1];
		
		u8MainOffset = u8Counter + u8RowOffset + MINIGAUSS_u8START_INDEX_2ND;
		*(pu8Storage+u8MainOffset) = au8AdcValues[MINIGAUSS_u8ANALOG_INPUT_2];
		
		u8MainOffset = u8Counter + u8RowOffset + MINIGAUSS_u8SENSOR_QUANTITY + MINIGAUSS_u8START_INDEX_2ND;
		*(pu8Storage+u8MainOffset) = au8AdcValues[MINIGAUSS_u8ANALOG_INPUT_3];
		
		if( ((u8Counter+1) % MINIGAUSS_u8SENSOR_QUANTITY) == 0 )
		{
			u8RowOffset += MINIGAUSS_u8SENSOR_QUANTITY;
		}
#endif /* MINIGAUSS_nDEVICE_TYPE == MINIGAUSS_n1x1_TYPE */
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
	for(uint8_t u8Index=0; MINIGAUSS_u8SENSOR_QUANTITY>u8Index; u8Index++)
	{
		adc_sync_set_inputs(&ADC_0, u8Index, CONF_ADC_0_MUXNEG, u8Index);
		adc_sync_read_channel(&ADC_0, u8Index, (pu8Values+u8Index), 1);
		
		//LOGDEBUG_vSendData((pu8Values+u8Index), 1);
	}
}

void MINIGAUSS_vGetDimensions(uint8_t *pu8Columns, uint8_t *pu8Rows)
{
	*pu8Columns = MINIGAUSS_nCOLUMNS;
	*pu8Rows = MINIGAUSS_nROWS;
}
