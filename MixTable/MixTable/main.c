#include <atmel_start.h>
#include <driver_examples.h>
#include <tag.h>
#include <logdebug.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	LOGDEBUG_vInit();
	TAG_vInit();
	
	TIMER_0_example();

	/* Replace with your application code */
	while (1) {
	}
}
