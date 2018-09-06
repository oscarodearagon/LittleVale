/*
 * imagetesting.h
 *
 * Created: 8/20/2018 9:06:34 PM
 *  Author: SirOscarin
 */ 


#ifndef IMAGETESTING_H_
#define IMAGETESTING_H_

#include <utils_assert.h>

uint8_t* IMAGETESTING_pu8GetDataArray(void);

void IMAGETESTING_vCopyArrays(uint8_t *pu8Source, uint8_t *pu8Destination, uint8_t u8Size);

void IMAGETESTING_vSubstractConstant(void);

void IMAGETESTING_vBinaryData(void);

void IMAGETESTING_vCentroid(void);

void IMAGETESTING_vCentroidFromSensor(uint8_t *pu8Source);

void IMAGETESTING_vSendCoordinates(uint16_t u16XAxis, uint16_t u16YAxis);

#endif /* IMAGETESTING_H_ */