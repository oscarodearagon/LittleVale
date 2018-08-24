/*
 * logdebug.h
 *
 * Created: 8/7/2018 7:31:23 PM
 *  Author: SirOscarin
 */ 


#ifndef LOGDEBUG_H_
#define LOGDEBUG_H_

#include "atmel_start_pins.h"
#include <utils_assert.h>

#define LOGDEBUG_u8DIGITAL_OUTPUT_0		(PA27)
#define LOGDEBUG_u8DIGITAL_OUTPUT_1		(PA06)

#ifdef __cplusplus
extern "C" {
#endif

	void LOGDEBUG_vInit(void);
	
	void LOGDEBUG_vSendData(uint8_t * pu8Data, uint16_t u16Length);
	
	uint16_t LOGDEBUG_u16GetArrayLength(const uint8_t *pu8String);
	
	void LOGDEBUG_vStartMeasurement(uint8_t u8Output);
	
	void LOGDEBUG_vStopMeasurement(uint8_t u8Output);

#ifdef __cplusplus
}
#endif


#endif /* LOGDEBUG_H_ */