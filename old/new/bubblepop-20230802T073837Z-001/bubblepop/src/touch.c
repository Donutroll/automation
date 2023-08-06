#include "touch.h"
#include "lpc24xx.h"

#define CS_PIN            0x00100000        //P0.20

static unsigned char touch_read(unsigned char command);

void touch_init(void)
{
	//Implement this as you see fit
	//Remember to setup CS_TP as a GPIO output
	PINSEL0 |= 0x3 << 30;
	PINSEL1 |= 0x3 << 2;
	PINSEL1 |= 0x3 << 4;
	PINSEL1 &= ~(0x00 << 8);
	//set as outp
	FIO0DIR |= CS_PIN;
	
	S0SPCR = 0x093C;
	S0SPCCR = 36;
}

void touch_read_xy(char *x, char* y)
{
	//Read X co-ordinate from the touch screen controller
	*x = touch_read(0xD8);
	//Read Y co-ordinate from the touch screen controller
	*y = touch_read(0x98);
}

void touch_read_z(char *x, char* y)
{
	//Read X co-ordinate from the touch screen controller
	*x = touch_read(0xB8);
	//Read Y co-ordinate from the touch screen controller
	*y = touch_read(0xC8);
}


static unsigned char touch_read(unsigned char command)
{
	unsigned short result;

	//Set CS_TP pin low to begin SPI transmission
	FIO0PIN &= ~CS_PIN;
	
	//Transmit command byte on MOSI, ignore MISO (full read write cycle)
	S0SPDR = command;
	while ((S0SPSR >> 7) == 0) {}
	
	//Transmit 0x00 on MOSI, read in requested result on MISO (another full read write cycle)
	S0SPDR = 0x00;
	while ((S0SPSR >> 7) == 0) {}
	result = S0SPDR;
	
	//Transmission complete, set CS_TP pin back to high
	FIO0PIN |= CS_PIN;
	
	//Return 8 bit result.
	return (unsigned char) result;
}	

