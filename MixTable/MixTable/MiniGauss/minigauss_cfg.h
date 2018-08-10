/*
 * minigauss_cfg.h
 *
 * Created: 8/7/2018 8:17:34 PM
 *  Author: SirOscarin
 */ 


#ifndef MINIGAUSS_CFG_H_
#define MINIGAUSS_CFG_H_

#include "atmel_start_pins.h"
#include <utils_assert.h>

#define MINIGAUSS_u8ANALOG_INPUT_0		(0)

#define MINIGAUSS_stDEVICE_TYPE			Basic //Complex

#define MINIGAUSS_u8INPUTS_PER_SENSOR	(16)

#if  (MINIGAUSS_stDEVICE_TYPE==Basic)
#define MINIGAUSS_u8SENSOR_QUANTITY		(1)
#else
#define MINIGAUSS_u8SENSOR_QUANTITY		(4)
#endif

/* GPIO OUTPUTS */
#define MINIGAUSS_u8DIGITAL_OUTPUT_0	(PA16)
#define MINIGAUSS_u8DIGITAL_OUTPUT_1	(PA17)
#define MINIGAUSS_u8DIGITAL_OUTPUT_2	(PA30)
#define MINIGAUSS_u8DIGITAL_OUTPUT_3	(PA31)

#endif /* MINIGAUSS_CFG_H_ */