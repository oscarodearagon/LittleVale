/*
 * application.c
 *
 * Created: 8/23/2018 8:28:30 PM
 *  Author: SirOscarin
 */ 

#include <application.h>
#include <sensor.h>
#include <logdebug.h>
#include <imagecalculations.h>
#include <imagetesting.h>

void APPLICATION_vInit(void)
{
	uint8_t u8Columns = 0;
	uint8_t u8Rows = 0;
	
	SENSOR_vGetDimensions(&u8Columns, &u8Rows);
	(void) IMAGECALCULATIONS_boInit(u8Columns , u8Rows);
	
	LOGDEBUG_vInit();
	SENSOR_vInit();
}

void APPLICATION_vCyclic(void)
{
	uint8_t *pu8Data = NULL;
	uint16_t u16XAxis = 0;
	uint16_t u16YAxis = 0;
	
	LOGDEBUG_vStartMeasurement(1);
	
	LOGDEBUG_vStartMeasurement(0);
	pu8Data = SENSOR_pu8ReadDevice();
	LOGDEBUG_vStopMeasurement(0);
		
	/* Send values through serial port */
	//SENSOR_vSendValues();
		
	/* Calculate Centroid */
	(void) IMAGECALCULATIONS_boGetCoordinates(pu8Data, &u16XAxis, &u16YAxis);
	
	/* Send values through serial port */
	LOGDEBUG_vStartMeasurement(0);
	IMAGETESTING_vSendCoordinates(u16XAxis, u16YAxis);
	LOGDEBUG_vStopMeasurement(0);
	
	LOGDEBUG_vStopMeasurement(1);
}