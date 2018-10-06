/* 
* AvrBldc.cpp
*
* Created: 06/10/2018 6:33:21
* Author: Arief Ismail
*/


#include "AvrBldc.h"


CAvrBldc bldc;

void CAvrBldc::init(){
	PORTA=0x22;
}


// default constructor
CAvrBldc::CAvrBldc()
{
} //AvrBldc

// default destructor
CAvrBldc::~CAvrBldc()
{
} //~AvrBldc