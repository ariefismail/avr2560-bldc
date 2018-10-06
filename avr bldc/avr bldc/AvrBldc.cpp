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
	DDRE=0xff;
	
	// HAL input from BLDC
	DDRB=0x00;
	
	// Timer3 init
	// timer freq =16000000/64 = 250000Hz
	TCCR3B |= 1<<0; 
	TCCR3B |= 1<<1;
	
	// Fast PWM top 1023
	TCCR3A |= 1;
	TCCR3A |= 1<<1;
	TCCR3B |= 1<<3;
}

void CAvrBldc::execute(uint16_t pwm){
	switch(halRead()){
		//	 0bABC
		case 0b011:
		disablePhase(A);	// A : NC
		pwmMode(A,PWM_DISABLE);
		
		enablePhase(B);		// B : +
		pwmMode(B,PWM_NON_INVERTING);
		
		enablePhase(C);		// C : -
		pwmMode(C,PWM_INVERTING);
		
		serial.print("1\r\n");
		break;
		
		case 0b001:
		enablePhase(A);		// A : -
		pwmMode(A,PWM_INVERTING);
		
		enablePhase(B);		// B : +
		pwmMode(B,PWM_NON_INVERTING);
		
		disablePhase(C);	// C : NC
		pwmMode(C,PWM_DISABLE);
		
		serial.print("2\r\n");
		break;
		
		case 0b101:
		enablePhase(A);		// A : -
		pwmMode(A,PWM_INVERTING);
		
		disablePhase(B);	// B : NC
		pwmMode(B,PWM_DISABLE);
		
		enablePhase(C);		// C : +
		pwmMode(C,PWM_NON_INVERTING);
		
		serial.print("3\r\n");
		break;
		
		case 0b100:
		disablePhase(A);	// A : NC
		pwmMode(A,PWM_DISABLE);
		
		enablePhase(B);		// B : -
		pwmMode(B,PWM_INVERTING);
		
		enablePhase(C);		// C : +
		pwmMode(C,PWM_NON_INVERTING);
		
		serial.print("4\r\n");
		break;
		
		case 0b110:
		enablePhase(A);		// A : +
		pwmMode(A,PWM_NON_INVERTING);
		
		enablePhase(B);		// B : -
		pwmMode(B,PWM_INVERTING);
		
		disablePhase(C);	// C : NC
		pwmMode(C,PWM_DISABLE);
		
		serial.print("5\r\n");
		break;
		
		case 0b010:
		enablePhase(A);		// A : +
		pwmMode(A,PWM_NON_INVERTING);
		
		disablePhase(B);	// B : NC
		pwmMode(B,PWM_DISABLE);
		
		enablePhase(C);		// C : -
		pwmMode(C,PWM_NON_INVERTING);
		
		serial.print("6\r\n");
		break;
		
		default:
		break;
		
	}
	OCR3A=pwm;
}

inline void CAvrBldc::pwmMode(enumPhase channel,enumMode mode){
	
	switch (channel){
		case A:
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
		
		case B:
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
		
		case C:
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

inline void CAvrBldc::enablePhase(enumPhase phase){
	PINE|=1<<(phase-1);
}

inline void CAvrBldc::disablePhase(enumPhase phase){
	PINE&=~(1<<(phase-1));
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