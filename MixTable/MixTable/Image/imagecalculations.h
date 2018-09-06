/*
 * imagecalculations.h
 *
 * Created: 8/16/2018 10:21:41 PM
 *  Author: SirOscarin
 */ 


#ifndef IMAGECALCULATIONS_H_
#define IMAGECALCULATIONS_H_

#include <utils_assert.h>

#ifdef __cplusplus
extern "C" {
	#endif

	bool IMAGECALCULATIONS_boInit(uint8_t u8Columns, uint8_t u8Rows);
	
	bool IMAGECALCULATIONS_boGetCoordinates(uint8_t *pu8Data, uint16_t *pu16XAxis, uint16_t *pu16YAxis);

	bool IMAGECALCULATIONS_boGetCentroid(uint8_t *pu8Data, uint16_t *pu16XAxis, uint16_t *pu16YAxis);
	
	void IMAGECALCULATIONS_vSubtractConstant(uint8_t *pu8Data, uint8_t u8Constant);
	
	void IMAGECALCULATIONS_vBinaryImage(uint8_t *pu8Data);

	#ifdef __cplusplus
}
#endif

#endif /* IMAGECALCULATIONS_H_ */