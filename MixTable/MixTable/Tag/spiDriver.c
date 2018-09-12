/*
 * spiDriver.c
 *
 * Created: 9/10/2018 10:53:42 PM
 *  Author: SirOscarin
 */ 

#include <spiDriver.h>
#include <hal_spi_m_sync.h>
#include <driver_init.h>

void SPIDRIVER_vInit(void)
{
	spi_m_sync_enable(&SPI_0);
}

int32_t SPIDRIVER_i32TransferByte(uint8_t u8TxData, uint8_t *pu8RxData)
{
	int32_t i32Status = 0;
	struct spi_xfer xTransfer = {.txbuf=&u8TxData, .rxbuf=pu8RxData, .size=1};
		
	i32Status = spi_m_sync_transfer(&SPI_0, &xTransfer);
	
	return i32Status;
}