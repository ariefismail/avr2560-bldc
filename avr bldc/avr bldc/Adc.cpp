/* 
* Adc.cpp
*
* Created: 16/10/2018 5:30:47
* Author: Arief Ismail
*/


#include "Adc.h"

void CAdc::init(){
	// avcc as adc reference
	ADMUX|=1<<6;
	
	// adc clock = systemclock / 128;
	ADCSRA|=7;
	
	//disable the digital input buffer on channel 0
	DIDR0|=1;
	
	// auto trigger adc
	ADCSRA|=1<<5;
	
	// enable adc
	ADCSRA|=1<<7;
	
	// start conversion
	ADCSRA|=1<<6;
}

void CAdc::execute(){
	if(! (ADCSRA>>6 & 1) ){
		
		//m_adc= ( ADCH << 8 ) & ADCL ;
		m_adc=ADCW;
		
		// start conversion again
		ADCSRA|=1<<6;
	}
}

uint16_t CAdc::adcRead(){
	return m_adc;
}

// default constructor
CAdc::CAdc()
{
} //Adc

// default destructor
CAdc::~CAdc()
{
} //~Adc
