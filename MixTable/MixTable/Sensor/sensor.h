/*
 * sensor.h
 *
 * Created: 8/7/2018 7:25:29 PM
 *  Author: SirOscarin
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_

#include <minigauss_cfg.h>

#define SENSOR_nCOLUMNS		MINIGAUSS_nCOLUMNS
#define SENSOR_nROWS		MINIGAUSS_nROWS

#ifdef __cplusplus
extern "C" {
#endif

	void SENSOR_vInit(void);
	
	uint8_t* SENSOR_pu8ReadDevice(void);
	
	void SENSOR_vSendValues(void);

#ifdef __cplusplus
}
#endif



#endif /* SENSOR_H_ */