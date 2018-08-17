/*
 * imagemoments.c
 *
 * Created: 8/16/2018 8:02:26 PM
 *  Author: SirOscarin
 */ 

#include <imagemoments.h>

static const uint8_t IMAGEMOMENTS_u8ColumnsMax = 8;
static const uint8_t IMAGEMOMENTS_u8RowsMax = 8;

static uint16_t IMAGEMOMENTS_u16Length = 0;
static uint8_t IMAGEMOMENTS_u8Columns = 0;
static uint8_t IMAGEMOMENTS_u8Rows = 0;

bool boInitImageMoments(uint8_t u8Columns, uint8_t u8Rows)
{
	bool boResult = false;
	
	if((IMAGEMOMENTS_u8ColumnsMax >= u8Columns) || (IMAGEMOMENTS_u8RowsMax >= u8Rows))
	{
		IMAGEMOMENTS_u8Columns = u8Columns;
		IMAGEMOMENTS_u8Rows = u8Rows;
		IMAGEMOMENTS_u16Length = u8Columns * u8Rows;
		boResult = true;
	}
	return boResult;
}

void vGetMoment_00(uint8_t *pu8Data, uint8_t *pu8Moment_00)
{
	uint8_t u8Counter = 0;
	uint8_t u8Moment_00 = 0;
	uint8_t u8Value = 0;	// If it is binary data it is enough to have it of 8bytes
	
	while(u8Counter < IMAGEMOMENTS_u16Length)
	{
		u8Value = *(pu8Data + u8Counter);
		if( u8Value != 0)
		{
			u8Moment_00 += u8Value;
		}
		u8Counter++;
	}
	
	*pu8Moment_00 = u8Moment_00;
}

void vGetMoment_10(uint8_t *pu8Data, uint16_t *pu16Moment_10)
{
	uint8_t u8Counter = 0;
	uint16_t u16Moment_10 = 0;
	uint8_t u8Value = 0;
	uint8_t u8FactorIndex = 0;
	uint8_t au8ColumnsSum[] = {0, 0, 0, 0, 0, 0, 0, 0};
		
	while(u8Counter < IMAGEMOMENTS_u16Length)
	{
		u8Value = *(pu8Data + u8Counter);
		
		if( u8Value != 0)
		{
			au8ColumnsSum[u8FactorIndex] += u8Value;
		}
		u8FactorIndex++;
		
		if(u8FactorIndex >= IMAGEMOMENTS_u8Columns)
		{
			u8FactorIndex = 0;
		}
		u8Counter++;
	}
	
	u8Counter=0;
	while(u8Counter < IMAGEMOMENTS_u8Columns)
	{
		u16Moment_10 += au8ColumnsSum[u8Counter] * (u8Counter + 1);
		u8Counter++;
	}
	
	*pu16Moment_10 = u16Moment_10;
}

bool boGetMoment_01(uint8_t *pu8Data, uint16_t *pu16Moment_01)
{
	uint8_t u8Counter = 0;
	uint16_t u16Moment_01 = 0;
	uint8_t u8Value = 0;
	uint8_t u8FactorIndex = 0;
	uint8_t au8RowsSum[] = {0, 0, 0, 0, 0, 0, 0, 0};
		
	while(u8Counter < IMAGEMOMENTS_u16Length)
	{
		u8Value = *(pu8Data + u8Counter);
			
		if( u8Value != 0)
		{
			au8RowsSum[u8FactorIndex] += u8Value;
		}
		
		if(((u8Counter + 1) % IMAGEMOMENTS_u8Columns) == 0)
		{
			u8FactorIndex++;
		}
		u8Counter++;
	}
		
	u8Counter=0;
	while(u8Counter < IMAGEMOMENTS_u8Rows)
	{
		u16Moment_01 += au8RowsSum[u8Counter] * (IMAGEMOMENTS_u8Rows - u8Counter);
		u8Counter++;
	}
		
	*pu16Moment_01 = u16Moment_01;
}