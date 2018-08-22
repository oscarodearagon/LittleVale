/*
 * imagemoments.h
 *
 * Created: 8/16/2018 8:02:54 PM
 *  Author: SirOscarin
 */ 


#ifndef IMAGEMOMENTS_H_
#define IMAGEMOMENTS_H_

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

	bool IMAGEMOMENTS_boInit(uint8_t u8Columns, uint8_t u8Rows);

	void IMAGEMOMENTS_vGet_00(uint8_t *pu8Data, uint8_t *pu8Moment_00);
	
	void IMAGEMOMENTS_vGet_10(uint8_t *pu8Data, uint16_t *pu16Moment_10);
	
	void IMAGEMOMENTS_vGet_01(uint8_t *pu8Data, uint16_t *pu16Moment_01);

#ifdef __cplusplus
}
#endif

#endif /* IMAGEMOMENTS_H_ */