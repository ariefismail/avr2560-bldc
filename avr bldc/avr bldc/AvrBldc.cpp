/* 
* AvrBldc.cpp
*
* Created: 06/10/2018 6:33:21
* Author: Arief Ismail
*/

#include "AvrBldc.h"

CAvrBldc bldc;

void CAvrBldc::init(){
	// PWM output of the mosfet gate driver
	DDRE=0x38;
	DDRH=0x38;
	
	// HAL input from BLDC
	DDRB=0x00;
	
	GTCCR|=1<<7;
	
	// Timer3 init
	// timer freq =16000000/64 = 250000Hz
	TCCR3B |= 1<<0; 
	TCCR3B |= 1<<1;
	
	// Fast PWM top 1023
	TCCR3A |= 1;
	TCCR3A |= 1<<1;
	TCCR3B |= 1<<3;
	
	// Timer4 init
	// timer freq =16000000/64 = 250000Hz
	TCCR4B |= 1<<0;
	TCCR4B |= 1<<1;
		
	// Fast PWM top 1023
	TCCR4A |= 1;
	TCCR4A |= 1<<1;
	TCCR4B |= 1<<3;
	
	// PWM0 PWM2 PMW4 INVERTING
	TCCR4A|=1<<7;
	TCCR4A|=1<<6;
	TCCR4A|=1<<5;
	TCCR4A|=1<<4;
	TCCR4A|=1<<3;
	TCCR4A|=1<<2;
	
	// PWM1 PWM3 PWM5 NON-INVERTING
	TCCR3A|=1<<7;
	TCCR3A&=~(1<<6);
	TCCR3A|=1<<5;
	TCCR3A&=~(1<<4);
	TCCR3A|=1<<3;
	TCCR3A&=~(1<<2);
	
	// START THE TIMER SYNC
	GTCCR=0;
}

void CAvrBldc::execute(uint16_t pwm){
	switch(halRead()){
		//	 0bABC
		case 0b011:
		pwmMode(0,PWM_DISABLE);
		pwmMode(1,PWM_DISABLE);
		pwmMode(2,PWM_DISABLE);
		
		pwmMode(3,PWM_NON_INVERTING);
		PWM3=1023;
		
		pwmMode(4,PWM_INVERTING);
		PWM4=pwm;
		pwmMode(5,PWM_NON_INVERTING);
		PWM5=pwm;

		break;
		
		case 0b001:
		pwmMode(2,PWM_DISABLE);
		pwmMode(4,PWM_DISABLE);
		pwmMode(5,PWM_DISABLE);
		
		pwmMode(3,PWM_NON_INVERTING);
		PWM3=1023;
		
		pwmMode(0,PWM_INVERTING);
		PWM0=pwm;
		pwmMode(1,PWM_NON_INVERTING);
		PWM1=pwm;
		break;
		
		case 0b101:
		pwmMode(2,PWM_DISABLE);
		pwmMode(3,PWM_DISABLE);
		pwmMode(4,PWM_DISABLE);
		
		pwmMode(5,PWM_NON_INVERTING);
		PWM5=1023;
		
		pwmMode(0,PWM_INVERTING);
		PWM0=pwm;
		pwmMode(1,PWM_NON_INVERTING);
		PWM1=pwm;
		break;
		
		case 0b100:
		pwmMode(0,PWM_DISABLE);
		pwmMode(1,PWM_DISABLE);
		pwmMode(4,PWM_DISABLE);
		
		pwmMode(5,PWM_NON_INVERTING);
		PWM5=1023;
		
		pwmMode(2,PWM_INVERTING);
		PWM2=pwm;
		pwmMode(3,PWM_NON_INVERTING);
		PWM3=pwm;
		break;
		
		case 0b110:
		pwmMode(0,PWM_DISABLE);
		pwmMode(4,PWM_DISABLE);
		pwmMode(5,PWM_DISABLE);
		
		pwmMode(1,PWM_NON_INVERTING);
		PWM1=1023;
		
		pwmMode(2,PWM_INVERTING);
		PWM2=pwm;
		pwmMode(3,PWM_NON_INVERTING);
		PWM3=pwm;
		break;
		
		case 0b010:
		pwmMode(0,PWM_DISABLE);
		pwmMode(2,PWM_DISABLE);
		pwmMode(3,PWM_DISABLE);
		
		pwmMode(1,PWM_NON_INVERTING);
		PWM1=1023;
		
		pwmMode(4,PWM_INVERTING);
		PWM4=pwm;
		pwmMode(5,PWM_NON_INVERTING);
		PWM5=pwm;
		break;
		
		default:
		break;
		
	}
}

inline void CAvrBldc::pwmMode(uint8_t channel,enumMode mode){
	
	switch (channel){
		case 0:
		switch(mode){
			case PWM_DISABLE:
			TCCR4A&=~(1<<7);
			TCCR4A&=~(1<<6);
			break;
			
			case PWM_NON_INVERTING:
			TCCR4A&=~(1<<6);
			TCCR4A|=1<<7;
			break;
			
			case PWM_INVERTING:
			TCCR4A|=1<<7;
			TCCR4A|=1<<6;
			break;
		}
		break;
		
		case 1:
		switch(mode){
			case PWM_DISABLE:
			TCCR3A&=~(1<<7);
			TCCR3A&=~(1<<6);
			break;
			
			case PWM_NON_INVERTING:
			TCCR3A&=~(1<<6);
			TCCR3A|=1<<7;
			break;
			
			case PWM_INVERTING:
			TCCR3A|=1<<7;
			TCCR3A|=1<<6;
			break;
		}
		break;

		case 2:
		switch(mode){
			case PWM_DISABLE:
			TCCR4A&=~(1<<5);
			TCCR4A&=~(1<<4);
			break;
			
			case PWM_NON_INVERTING:
			TCCR4A&=~(1<<4);
			TCCR4A|=1<<5;
			break;
			
			case PWM_INVERTING:
			TCCR4A|=1<<5;
			TCCR4A|=1<<4;
			break;
		}
		break;
		
		case 3:
		switch(mode){
			case PWM_DISABLE:
			TCCR3A&=~(1<<5);
			TCCR3A&=~(1<<4);
			break;
			
			case PWM_NON_INVERTING:
			TCCR3A&=~(1<<4);
			TCCR3A|=1<<5;
			break;
			
			case PWM_INVERTING:
			TCCR3A|=1<<5;
			TCCR3A|=1<<4;
			break;
		}
		break;

		case 4:
		switch(mode){
			case PWM_DISABLE:
			TCCR4A&=~(1<<3);
			TCCR4A&=~(1<<2);
			break;
			
			case PWM_NON_INVERTING:
			TCCR4A&=~(1<<2);
			TCCR4A|=1<<3;
			break;
			
			case PWM_INVERTING:
			TCCR4A|=1<<3;
			TCCR4A|=1<<2;
			break;
		}
		break;
		
		case 5:
		switch(mode){
			case PWM_DISABLE:
			TCCR3A&=~(1<<3);
			TCCR3A&=~(1<<2);
			break;
			
			case PWM_NON_INVERTING:
			TCCR3A&=~(1<<2);
			TCCR3A|=1<<3;
			break;
			
			case PWM_INVERTING:
			TCCR3A|=1<<3;
			TCCR3A|=1<<2;
			break;
		}
		break;
	}
	
}


inline uint8_t CAvrBldc::halRead(){
	return PINB & 0x07;
}

// default constructor
CAvrBldc::CAvrBldc()
{
} //AvrBldc

// default destructor
CAvrBldc::~CAvrBldc()
{
} //~AvrBldc