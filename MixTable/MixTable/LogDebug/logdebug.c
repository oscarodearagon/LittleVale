/*
 * logdebug.c
 *
 * Created: 8/7/2018 7:50:32 PM
 *  Author: SirOscarin
 */ 


#include <logdebug.h>
#include <hal_usart_sync.h>
#include <hal_gpio.h>

extern struct usart_sync_descriptor USART_0;

static struct io_descriptor *LOGDEBUG_pstIo = NULL;

void LOGDEBUG_vInit(void)
{
	/* Serial output */
	usart_sync_get_io_descriptor(&USART_0, &LOGDEBUG_pstIo);
	usart_sync_enable(&USART_0);
	
	/* Pins to measure time */
	gpio_set_pin_direction(LOGDEBUG_u8DIGITAL_OUTPUT_0, GPIO_DIRECTION_OUT);
	gpio_set_pin_direction(LOGDEBUG_u8DIGITAL_OUTPUT_1, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_0, false);
	gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_1, false);
	
}

void LOGDEBUG_vSendData(uint8_t * pu8Data, uint16_t u16Length)
{
	io_write(LOGDEBUG_pstIo, pu8Data, u16Length);
}

uint16_t LOGDEBUG_u16GetArrayLength(const uint8_t *pu8String)
{
	uint16_t u16Length;
	const uint8_t *pu8Reference;
	
	for (pu8Reference = pu8String; *pu8Reference; ++pu8Reference);
	
	u16Length = (uint16_t) (pu8Reference - pu8String);
	return(u16Length);
}

void LOGDEBUG_vStartMeasurement(uint8_t u8Output)
{
	if(u8Output == 0)
	{
		gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_0, true);
	}
	else if (u8Output == 1)
	{
		gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_1, true);
	}
	else
	{
		/* It should not be executed */
	}
}
	
void LOGDEBUG_vStopMeasurement(uint8_t u8Output)
{
	if(u8Output == 0)
	{
		gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_0, false);
	}
	else if (u8Output == 1)
	{
		gpio_set_pin_level(LOGDEBUG_u8DIGITAL_OUTPUT_1, false);
	}
	else
	{
		/* It should not be executed */
	}
}