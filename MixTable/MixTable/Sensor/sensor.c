/*
 * sensor.c
 *
 * Created: 8/7/2018 7:51:00 PM
 *  Author: SirOscarin
 */ 

#include <sensor.h>
#include <minigauss.h>

void SENSOR_vInit(void)
{
	MINIGAUSS_vInit();
}
	
void SENSOR_vReadDevice(void)
{
	MINIGAUSS_vReadDevice();
}