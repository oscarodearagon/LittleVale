/*
 * minigauss_cfg.h
 *
 * Created: 8/7/2018 8:17:34 PM
 *  Author: SirOscarin
 */ 


#ifndef MINIGAUSS_CFG_H_
#define MINIGAUSS_CFG_H_

#include <utils_assert.h>

#define MINIGAUSS_u8ANALOG_INPUT_0		(0)

#define MINIGAUSS_stDEVICE_TYPE			Basic //Complex

#define MINIGAUSS_u8INPUTS_PER_SENSOR	(16)

#if  (MINIGAUSS_stDEVICE_TYPE==Basic)
#define MINIGAUSS_u8SENSOR_QUANTITY		(1)
#else
#define MINIGAUSS_u8SENSOR_QUANTITY		(4)
#endif

#endif /* MINIGAUSS_CFG_H_ */