/*
 * minigauss.h
 *
 * Created: 8/7/2018 7:28:34 PM
 *  Author: SirOscarin
 */ 


#ifndef MINIGAUSS_H_
#define MINIGAUSS_H_

#ifdef __cplusplus
extern "C" {
#endif

	void MINIGAUSS_vInit(void);
	
	void MINIGAUSS_vReadDevice(void);
	
	void MINIGAUSS_vGetAdcValues(void);
	
	void MINIGAUSS_vProcess(void);

#ifdef __cplusplus
}
#endif


#endif /* MINIGAUSS_H_ */