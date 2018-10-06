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

	enum enumPhase{
		A=1,
		B=2,
		C=3
	};
	
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
	inline void pwmMode(enumPhase channel,enumMode mode);
	inline void enablePhase(enumPhase phase);
	inline void disablePhase(enumPhase phase);
	
	inline uint8_t halRead();

private:

}; //AvrBldc

extern CAvrBldc bldc;

#endif //__AVRBLDC_H__
