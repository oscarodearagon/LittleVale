/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"
#include <hpl_spi.h>
#include <tag.h>
#include <logdebug.h>

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using SPI_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_0[12] = "Hello World!";

void SPI_0_example(void)
{
	struct io_descriptor *io;
	
	uint8_t au8RxBuff[12];
	uint32_t u32Status;
	
	struct spi_xfer xTransfer = {.txbuf=example_SPI_0, .rxbuf=au8RxBuff, .size=12};
	spi_m_sync_get_io_descriptor(&SPI_0, &io);

	gpio_set_pin_level(PA23, false);		// SS-Low
	
	spi_m_sync_enable(&SPI_0);
	//io_write(io, example_SPI_0, 12);
	
	u32Status = spi_m_sync_transfer(&SPI_0, &xTransfer);
	
	gpio_set_pin_level(PA23, true);		// SS-High
}

/**
 * Example of using USART_1 to write "Hello World" using the IO abstraction.
 */
void USART_1_example(void)
{
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_1, &io);
	usart_sync_enable(&USART_1);

	io_write(io, (uint8_t *)"Hello World!", 12);
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;
/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
	//SPI_0_example();
	
	bool boResult = false;
	uint8_t u8Id = 0;
	
	boResult = TAG_boGetId(&u8Id);
	
	if(true == boResult)
	{
		LOGDEBUG_vSendData(&u8Id, 1);
	}
	
}

void TIMER_0_example(void)
{
	gpio_set_pin_direction(PA23, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PA23, true);
	
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 1000;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}