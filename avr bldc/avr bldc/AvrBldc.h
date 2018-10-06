/* 
* AvrBldc.h
*
* Created: 06/10/2018 6:33:21
* Author: Arief Ismail
*/


#ifndef __AVRBLDC_H__
#define __AVRBLDC_H__

#include <avr/io.h>
#include "Serial.h"

#define PWM0 OCR4A 
#define PWM1 OCR3A
#define PWM2 OCR4B
#define PWM3 OCR3B
#define PWM4 OCR4C
#define PWM5 OCR3C

	
	enum enumMode{
		PWM_DISABLE=0,
		PWM_NON_INVERTING=1,
		PWM_INVERTING=2
	};

class CAvrBldc
{
public:
	CAvrBldc();
	~CAvrBldc();
	void init();
	void execute(uint16_t pwm);
	inline void pwmMode(uint8_t channel,enumMode mode);
	inline uint8_t halRead();

private:

}; //AvrBldc

extern CAvrBldc bldc;

#endif //__AVRBLDC_H__
