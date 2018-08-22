#include <atmel_start.h>
#include <timer.h>
#include <sensor.h>
#include <logdebug.h>
#include <imagecalculations.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initializations */
	(void) IMAGECALCULATIONS_boInitImageCalculations(4 , 4);
	LOGDEBUG_vInit();
	SENSOR_vInit();
	TIMER_vInit();

	/* Replace with your application code */
	while (1) {
	}
}
