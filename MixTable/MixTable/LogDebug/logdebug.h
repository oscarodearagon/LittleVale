/*
 * logdebug.h
 *
 * Created: 8/7/2018 7:31:23 PM
 *  Author: SirOscarin
 */ 


#ifndef LOGDEBUG_H_
#define LOGDEBUG_H_

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

	void LOGDEBUG_vInit(void);
	
	void LOGDEBUG_vSendData(uint8_t * pu8Data, uint16_t u16Length);
	
	uint16_t LOGDEBUG_u16GetArrayLength(const uint8_t *pu8String);

#ifdef __cplusplus
}
#endif


#endif /* LOGDEBUG_H_ */