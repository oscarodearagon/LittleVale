/*
 * imagecalculations.c
 *
 * Created: 8/16/2018 10:21:22 PM
 *  Author: SirOscarin
 */ 

#include <imagecalculations.h>
#include <imagemoments.h>

static uint8_t IMAGEMOMENTS_u8DivisorMax = 0;

bool boInitImageCalculations(uint8_t u8Columns, uint8_t u8Rows)
{
	bool boResult = boInitImageMoments(u8Columns, u8Rows);
	
	IMAGEMOMENTS_u8DivisorMax = u8Columns * u8Rows;
	
	return boResult;
}

bool boGetCentroid(uint8_t *pu8Data, uint8_t *pu8XAxis, uint8_t *pu8YAxis)
{
	uint8_t u8Moment_00 = 0;
	uint16_t u16Moment_10 = 0;
	uint16_t u16Moment_01 = 0;
	bool boResult = false;
	
	vGetMoment_00(pu8Data, &u8Moment_00);
	vGetMoment_10(pu8Data, &u16Moment_10);
	vGetMoment_01(pu8Data, &u16Moment_01);
	
	if(u8Moment_00 != 0)
	{
		*pu8XAxis = (uint8_t)((u16Moment_10*IMAGEMOMENTS_u8DivisorMax) / u8Moment_00);
		*pu8YAxis = (uint8_t)((u16Moment_01*IMAGEMOMENTS_u8DivisorMax) / u8Moment_00);
	}
	
	return boResult;
}