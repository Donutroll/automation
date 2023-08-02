#include "lpc24xx.h"
#include <stdint.h>
#include "profile.h"
#include "timer.h"
#include "automation.h"
#include "../lcd/lcd_hw.h"
#include "../lcd/lcd_grph.h"
#include "../lcd/lcd_cfg.h"
#include "../lcd/sdram.h"
#include "drawTime.h"

#define CLOCKX 0
#define CLOCKY 0
#define CLOCKWIDTH 60
#define CLOCKHEIGHT 25


#define minute time & 0x1F
#define hour time << 6
extern uint16_t data[];

void init() {
	
	//LCD setup
	/*sdramInit();
	lcdInit(&lcd_config); 
	lcdTurnOn();
	lcd_fillScreen(BLACK);*/
	
	//system clock
	initClock();
	
	//ADC
	initADC();
	
	
	//initialise ui clock
	//drawTime(0,0,CLOCKX,CLOCKY, CLOCKX + CLOCKWIDTH, CLOCKY + CLOCKHEIGHT);
}


int main(void) {
	
	profile admin;
	uint8_t hourNow = 100;

	admin.name = "admin";
	admin.data = data;
	admin.useSensor = 0;
	
	init();
	
	
	while(1) {
		if (admin.useSensor) {
			if (readSensor() < 0.2f)
				FIO2PIN |= 0x3 << 4; //toggle leds
			else
				FIO2PIN &= ~(0x3 << 4); //toggle leds
		}
		else if (hourNow != getHour()) {//update every hour
			hourNow = getHour();
			updateDevices(&admin, hourNow);
		}
		
	}
	return 0;
}
