/*
 * sensor.h
 *
 * Created: 8/7/2018 7:25:29 PM
 *  Author: SirOscarin
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

	void SENSOR_vInit(void);
	
	void SENSOR_vReadDevice(void);

#ifdef __cplusplus
}
#endif



#endif /* SENSOR_H_ */