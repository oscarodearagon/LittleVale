/*
 * minigauss.h
 *
 * Created: 8/7/2018 7:28:34 PM
 *  Author: SirOscarin
 */ 


#ifndef MINIGAUSS_H_
#define MINIGAUSS_H_

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

	void MINIGAUSS_vInit(void);
	
	void MINIGAUSS_vReadDevice(uint8_t *pu8Storage);
	
	void MINIGAUSS_vSaveAdcValues(uint8_t *pu8Storage);
	
	void MINIGAUSS_vSetGpioOutputs(uint8_t u8Value);
	
	void MINIGAUSS_vDelay(uint8_t u8Loops);
	
	void MINIGAUSS_vReadAdcValues(uint8_t *pu8Values);

#ifdef __cplusplus
}
#endif


#endif /* MINIGAUSS_H_ */