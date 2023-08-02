#include "lpc24xx.h"
#include "timer.h"
#include "profile.h"
#include <stdint.h>

#define LRED 1 << 16
#define LGREEN 1 << 17
#define LBLUE 1 << 18

#define RRED 1 << 19
#define RGREEN 1 << 20
#define RBLUE 1 << 21

#define Rled 0
#define Lled 1

#define blind1 ((FIO2PIN >> 1) & 0x1)
#define blind2 ((FIO2PIN >> 2) & 0x1)
#define blind3 ((FIO2PIN >> 3) & 0x1)
#define light1 ((FIO2PIN >> 4) & 0x1)
#define light2 ((FIO2PIN >> 5) & 0x1)
#define sprinkler ((FIO2PIN >> 6) & 0x1)


#define ADCHANNEL 0x2
#define CLKDIV 3 << 8 // The APB clock (PCLK) is divided by (this value plus one) 
											// to produce the clock for the A/D converter, which should be less than or equal to 4.5 MHz


void configureLadder() {
	
	PINSEL4 = 0; //set to GPIO
	
	FIO0DIR |= 0x1 << 22;	//ladder enable output
	FIO2DIR |= 0xFF << 1; //ladder leds output
	
	//enable
	FIO0SET = 0x1 << 22; //ladder
	
	//set ladder leds to 0
	FIO2PIN &= ~(0xFF << 1);
}


void updateDevices(profile *p, uint8_t i) {
	configureLadder();//give IO to ladder

	FIO2PIN = (FIO2PIN & ~(0xFF << 1)) | p->data[i] << 1; //read bit pattern
	
	PINSEL4  = (PINSEL4 & 0xF0300000) | 0x014FFFFF; //return control to LCD
	return;
		
}
	

float readSensor() {
	float x = 0;
	
	AD0CR |= 1 << 24; //start conversion
	while(!(AD0DR1 & (1U << 31)));//wait till complete
	x = (((AD0DR1 >> 6)& 0x3FF)/1023.0f)*3.3f; //2^10 resolution with 3.3 voltage reference

	AD0CR ^= 1 << 24; //power down
	return x;
}

void initADC() {
	PCONP |= 0x1 << 12;	//enable dac
	PINSEL1 = (PINSEL1 & ~(0x5 << 16)) | 0x5 << 16;	//set P0.24 to AD0
	AD0CR =	ADCHANNEL | CLKDIV;	//configure ADC port set clk speed to 4.5Mhz
	AD0CR |= 1 << 21;	//set to operational mode
}
