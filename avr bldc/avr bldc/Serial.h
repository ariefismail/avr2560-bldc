/* 
* Serial.h
*
* Created: 06/10/2018 9:14:24
* Author: Arief Ismail
*/


#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <avr/io.h>

class CSerial
{

public:
	CSerial();
	~CSerial();
	void init(uint32_t baudrate);
	//void putchar(char data);
	void print(const char *data);
	void print(char *data);
private:

}; //Serial

extern CSerial serial;

#endif //__SERIAL_H__
