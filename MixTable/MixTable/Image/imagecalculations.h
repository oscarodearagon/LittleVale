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

	bool boInitImageCalculations(uint8_t u8Columns, uint8_t u8Rows);

	bool boGetCentroid(uint8_t *pu8Data, uint8_t *pu8XAxis, uint8_t *pu8YAxis);

	#ifdef __cplusplus
}
#endif

#endif /* IMAGECALCULATIONS_H_ */