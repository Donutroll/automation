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


#define ADCHANNEL 0x2
#define CLKDIV 3 << 8 // The APB clock (PCLK) is divided by (this value plus one) to produce the clock for the A/D converter, which should be less than or equal to 4.5 MHz
//configure to lpc clock speed
//calibrate to avg temperature



uint8_t setDevices(profile p, uint8_t states) {
	uint8_t i = getHour() - 1;
	
	if ((p.Rlight[i] & 0x1) ^ ((states >> Rled) & 0x1)) {
		FIO3PIN ^= LRED | LGREEN | LBLUE;
		states ^= Rled;
	}
	if ((p.Llight[i] & 0x1) ^ ((states >> Lled) & 0x1)) {
		FIO3PIN ^= LRED | LGREEN | LBLUE;
		states ^= Lled;
	}
	
	return states;
}
	

float readSensor() {
	float x = 1;

	PINSEL1 = 0x5 << 14;	//set P0.24 to AD0
	AD0CR =	ADCHANNEL | CLKDIV;	//configure ADC port set clk speed to 4.5Mhz
	AD0CR |= 1 << 21;	//operational mode
	
	FIO3DIR = 0x7 << 16; //configure left LED as output	
	
	while (1) {
			AD0CR |= 1 << 24; //start conversion
			while(!(AD0DR1 & (1U << 31)));//wait till complete
			x = (((AD0DR1 >> 6)& 0x3FF)/1023.0f)*3.3f; //2^10 resolution with 3.3vref
	}
	
	return x;
}