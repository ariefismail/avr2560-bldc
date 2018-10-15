/* 
* Adc.h
*
* Created: 16/10/2018 5:30:47
* Author: Arief Ismail
*/


#ifndef __ADC_H__
#define __ADC_H__

#include <avr/io.h>

class CAdc
{
//functions
public:
	void init();
	void execute();
	uint16_t adcRead();	

	CAdc();
	~CAdc();
private:
	uint16_t m_adc;

}; //Adc

#endif //__ADC_H__
