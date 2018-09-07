#include <atmel_start.h>
#include <application.h>
#include <timer.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Initializations */
	APPLICATION_vInit();
	TIMER_vInit();

	/* Replace with your application code */
	while (1) {
	}
}
