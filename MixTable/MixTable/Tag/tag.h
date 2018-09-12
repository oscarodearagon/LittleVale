/*
 * tag.h
 *
 * Created: 9/10/2018 10:12:24 PM
 *  Author: SirOscarin
 */ 


#ifndef TAG_H_
#define TAG_H_

#include <utils_assert.h>
#include <atmel_start_pins.h>

#define TAG_CHIP_SELECT_PIN		(PA23)
#define TAG_RESET_PIN			(PA28)

#define TAG_nAVAILABLE_IDS		(5)

#ifdef __cplusplus
extern "C" {
	#endif

	void TAG_vInit(void);
	
	bool TAG_boGetId(uint8_t *pu8Id);
	
	uint8_t TAG_u8DecodeId(void);

#ifdef __cplusplus
}
#endif

#endif /* TAG_H_ */