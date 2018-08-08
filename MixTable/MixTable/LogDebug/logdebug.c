/*
 * logdebug.c
 *
 * Created: 8/7/2018 7:50:32 PM
 *  Author: SirOscarin
 */ 


#include <logdebug.h>
#include <hal_usart_sync.h>

extern struct usart_sync_descriptor USART_0;

static struct io_descriptor *LOGDEBUG_pstIo = NULL;

void LOGDEBUG_vInit(void)
{
	usart_sync_get_io_descriptor(&USART_0, &LOGDEBUG_pstIo);
	usart_sync_enable(&USART_0);
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