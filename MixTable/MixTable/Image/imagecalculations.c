/*
 * imagecalculations.c
 *
 * Created: 8/16/2018 10:21:22 PM
 *  Author: SirOscarin
 */ 

#include <imagecalculations.h>
#include <imagemoments.h>
#include <logdebug.h>

static uint8_t IMAGEMOMENTS_u8DataLength = 0;

static uint8_t IMAGECALCULATIONS_nSubstractConst = 197;
static uint8_t IMAGECALCULATIONS_nThreshold = 25;

bool IMAGECALCULATIONS_boInit(uint8_t u8Columns, uint8_t u8Rows)
{
	bool boResult = IMAGEMOMENTS_boInit(u8Columns, u8Rows);
	
	IMAGEMOMENTS_u8DataLength = u8Columns * u8Rows;
	
	return boResult;
}

bool IMAGECALCULATIONS_boGetCoordinates(uint8_t *pu8Data, uint8_t *pu8XAxis, uint8_t *pu8YAxis)
{
	bool boResult = false;
	
	LOGDEBUG_vStartMeasurement(0);
	IMAGECALCULATIONS_vSubtractConstant(pu8Data, IMAGECALCULATIONS_nSubstractConst);
	LOGDEBUG_vStopMeasurement(0);
	
	LOGDEBUG_vStartMeasurement(0);
	IMAGECALCULATIONS_vBinaryImage(pu8Data);
	LOGDEBUG_vStopMeasurement(0);
	
	LOGDEBUG_vStartMeasurement(0);
	boResult = IMAGECALCULATIONS_boGetCentroid(pu8Data, pu8XAxis, pu8YAxis);
	LOGDEBUG_vStopMeasurement(0);
	
	return boResult;
}

bool IMAGECALCULATIONS_boGetCentroid(uint8_t *pu8Data, uint8_t *pu8XAxis, uint8_t *pu8YAxis)
{
	uint8_t u8DivisorMax = IMAGEMOMENTS_u8DataLength;
	uint8_t u8Moment_00 = 0;
	uint16_t u16Moment_10 = 0;
	uint16_t u16Moment_01 = 0;
	bool boResult = false;
	
	IMAGEMOMENTS_vGet_00(pu8Data, &u8Moment_00);
	IMAGEMOMENTS_vGet_10(pu8Data, &u16Moment_10);
	IMAGEMOMENTS_vGet_01(pu8Data, &u16Moment_01);
	
	if(u8Moment_00 != 0)
	{
		*pu8XAxis = (uint8_t)((u16Moment_10*u8DivisorMax) / u8Moment_00);
		*pu8YAxis = (uint8_t)((u16Moment_01*u8DivisorMax) / u8Moment_00);
	}
	else
	{
		*pu8XAxis = 0;
		*pu8YAxis = 0;
	}
	
	return boResult;
}

void IMAGECALCULATIONS_vSubtractConstant(uint8_t *pu8Data, uint8_t u8Constant)
{
	uint8_t u8Counter = 0;
	uint8_t u8Value = 0;
	
	while(u8Counter < IMAGEMOMENTS_u8DataLength)
	{
		u8Value = *(pu8Data+u8Counter);
		if(u8Value > u8Constant)
		{
			*(pu8Data+u8Counter) = u8Value - u8Constant;
		}
		else
		{
			*(pu8Data+u8Counter) = 0;
		}
		
		u8Counter++;
	}
}

void IMAGECALCULATIONS_vBinaryImage(uint8_t *pu8Data)
{
	uint8_t u8Counter = 0;
	uint8_t u8Value = 0;
	
	while(u8Counter < IMAGEMOMENTS_u8DataLength)
	{
		u8Value = *(pu8Data+u8Counter);
		if(u8Value > IMAGECALCULATIONS_nThreshold)
		{
			*(pu8Data+u8Counter) = 1;
		}
		else
		{
			*(pu8Data+u8Counter) = 0;
		}
		
		u8Counter++;
	}
}
