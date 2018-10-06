/* 
* AvrBldc.h
*
* Created: 06/10/2018 6:33:21
* Author: Arief Ismail
*/


#ifndef __AVRBLDC_H__
#define __AVRBLDC_H__

#include <avr/io.h>

class CAvrBldc
{
//variables
public:
protected:
private:

//functions
public:
	CAvrBldc();
	~CAvrBldc();
	void init();
protected:
private:
	CAvrBldc( const CAvrBldc &c );
	CAvrBldc& operator=( const CAvrBldc &c );

}; //AvrBldc

extern CAvrBldc bldc;

#endif //__AVRBLDC_H__
