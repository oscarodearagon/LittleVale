/*
 * spiDriver.h
 *
 * Created: 9/10/2018 10:53:22 PM
 *  Author: SirOscarin
 */ 


#ifndef SPIDRIVER_H_
#define SPIDRIVER_H_

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

	void SPIDRIVER_vInit(void);
	
	int32_t SPIDRIVER_i32TransferByte(uint8_t u8TxData, uint8_t *pu8RxData);

#ifdef __cplusplus
}
#endif



#endif /* SPIDRIVER_H_ */