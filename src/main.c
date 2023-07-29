#include "lpc24xx.h"
#include <stdint.h>
#include "profile.h"
#include "timer.h"
#include "automation.h"
#include "../lcd/lcd_hw.h"
#include "../lcd/lcd_grph.h"
#include "../lcd/lcd_cfg.h"
#include "../lcd/sdram.h"
#define minute time & 0x1F
#define hour time << 6

extern uint16_t data[];

void init() {

	
	//system clock
	initClock();
	
	//ADC
	initADC();
	
	//set output
	FIO0DIR |= 0x1 << 22;	//ladder enable
	FIO2DIR |= 0xFE << 1; //ladder leds
	FIO3DIR |= 0x3F << 16; //RGB leds
	
	//enable
	FIO0SET = 0x1 << 22; //ladder
	
	//set ladder leds to 0
	FIO2PIN &= ~(0xFE << 1);
	
	/*
	//LCD setup
	sdramInit();
	lcdInit(&lcd_config); 
	lcdTurnOn();
	lcd_fillScreen(BLACK);
	*/
}


int main(void) {
	
	profile admin;
	uint8_t prevHour = 100;
	
	admin.name = "admin";
	admin.data = data;
	admin.useSensor = 0;
	
	init();
	
	while(1) {
		if (admin.useSensor && (readSensor() < 0.2f)) {
				FIO2PIN |= 0x3 << 4;
		}
		else if (prevHour != getHour()) {
			prevHour = getHour();
			updateDevices(admin);
		}
		
	}
	return 0;
}
