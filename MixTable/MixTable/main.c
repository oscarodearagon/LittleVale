#include <atmel_start.h>
#include <timer.h>
#include <sensor.h>
#include <logdebug.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initializations */
	LOGDEBUG_vInit();
	SENSOR_vInit();
	TIMER_vInit();

	/* Replace with your application code */
	while (1) {
	}
}
