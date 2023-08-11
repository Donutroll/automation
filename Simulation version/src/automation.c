#include "lpc24xx.h"
#include "timer.h"
#include "profile.h"
#include <stdint.h>

#define LRED 1 << 16
#define LGREEN 1 << 17
#define LBLUE 1 << 18

#define LWHITE LRED | LGREEN | LBLUE

#define RRED 1 << 19
#define RGREEN 1 << 20
#define RBLUE 1 << 21

#define RWHITE RRED | RGREEN | RBLUE

#define MIN_BRIGHTNESS 0.2f
#define ADCHANNEL 0x2
#define CLKDIV 3 << 8 // The APB clock (PCLK) is divided by (this value plus one) 
											// to produce the clock for the A/D converter, which should be less than or equal to 4.5 MHz


void configureLadder() {
	
	PINSEL4 &= ~0x11; //set to GPIO
	
	//set as output
	FIO0DIR |= 0x1 << 22;	//ladder output
	FIO2DIR |= 0xFF << 1; //ladder leds output
	FIO3DIR |= 0x3F << 16; //RGB leds output
	
	//enable
	FIO0SET = 0x1 << 22; //led ladder
}

float readSensor() {
	float x = 0;
	
	AD0CR |= 1 << 24; //start conversion
	while(!(AD0DR1 & (1U << 31)));//wait till complete
	x = (((AD0DR1 >> 6)& 0x3FF)/1023.0f)*3.3f; //2^10 resolution with 3.3 voltage reference

	AD0CR ^= 1 << 24; //power down
	return x;
}


//bit 1 -> sprinkler
//Rled -> light 1
//Lled -> light 2
//bit 6~8 -> blind 1~3
void configureDevices(uint8_t control) {	

	//get bits
	uint8_t blinds = control & 0x7;
	uint8_t sprinkler = (control >> 5) & 0x1;
	uint8_t lights = (control >> 3) & 0x3;
	uint32_t Rled = (lights & 0x1) ? RWHITE : 0x0;
	uint32_t Lled = (lights & 0x2) ? LWHITE : 0x0;
	
	//write to corresponding leds
	FIO2PIN = (FIO2PIN & ~(0xFF << 1)) | (blinds << 6 | sprinkler << 1);
	FIO3PIN = (FIO3PIN & ~(0x3F << 16)) | Rled | Lled;
 }

void updateDevices(profile *p, uint8_t i, uint8_t update) {
	
	uint8_t control = 0;
	
	if (update)
		control = p->data[i]; //read bit pattern
	
	if (p->useSensor) {
	if (readSensor() < MIN_BRIGHTNESS)
		control |= 0x3 << 3; //toggle lights on
	else
		control &= ~(0x3 << 3); //toggle lights off
	}
	
	configureDevices(control);
	
	return;
}
	


void initADC() {
	PCONP |= 0x1 << 12;	//enable dac
	PINSEL1 = (PINSEL1 & ~(0x5 << 16)) | 0x5 << 16;	//set P0.24 to AD0
	AD0CR =	ADCHANNEL | CLKDIV;	//configure ADC port set clk speed to 4.5Mhz
	AD0CR |= 1 << 21;	//set to operational mode
}
