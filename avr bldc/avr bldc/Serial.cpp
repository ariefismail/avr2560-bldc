/* 
* Serial.cpp
*
* Created: 06/10/2018 9:14:24
* Author: Arief Ismail
*/


#include "Serial.h"

CSerial serial;

void CSerial::init(uint32_t baudrate){
	// uart transmit enable
	UCSR1B|=1<<3;
	
	uint16_t brrRegister = (16000000UL/(baudrate*16))-1;
	
	UBRR1H= (brrRegister>>8)&0x0f;
	UBRR1L= brrRegister & 0xff;
}

//void CSerial::putchar(char data){
	//while ( !( UCSR1A & (1<<UDRE1))) ;
	//
	//UDR1 = data;
//}

void CSerial::print(const char *data){
	while (*data){
		while ( !( UCSR1A & (1<<UDRE1))) ;
		UDR1 = *data;
		data++;
	}
}

void CSerial::print(char *data){
	while (*data){
		while ( !( UCSR1A & (1<<UDRE1))) ;
		UDR1 = *data;
		data++;
	}
}

// default constructor
CSerial::CSerial()
{
} //Serial

// default destructor
CSerial::~CSerial()
{
} //~Serial
