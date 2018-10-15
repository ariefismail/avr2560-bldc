#include <avr/io.h>
#include <stdio.h>
#include "AvrBldc.h"
#include "Serial.h"
#include "Adc.h"

CAdc adc;

int main(void)
{
	adc.init();
	serial.init(57600);
	bldc.init();
	while (1) 
    {
		adc.execute();
		//char buf[30];
		//sprintf(buf,"%d\r\n",adc.adcRead());
		//serial.print(buf);
		//serial.putchar('a');
		//serial.print("322\r\n");
		bldc.execute(adc.adcRead());
    }
}

