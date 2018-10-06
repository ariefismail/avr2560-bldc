#include <avr/io.h>
#include "AvrBldc.h"
#include "Serial.h"

int main(void)
{
	serial.init(57600);
	bldc.init();
	while (1) 
    {
		//serial.putchar('a');
		//serial.print("322\r\n");
		bldc.execute(322);
    }
}


