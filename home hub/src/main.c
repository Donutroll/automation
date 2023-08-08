#include "touch.h"
#include "lcd/lcd_hw.h"
#include "lcd/lcd_grph.h"
#include "lcd/lcd_cfg.h"
#include "lcd/sdram.h"
#include <stdio.h>
#include "drawTime.h"
#include "timer.h"
#include <LPC23xx.H>
#include "automation.h"

extern uint16_t data[];
#define true 1
#define false 0

#define CLOCKX 0
#define CLOCKY 0
#define CLOCKWIDTH 60
#define CLOCKHEIGHT 27

float getPressure(int x, int z1, int z2) {
	float pressure = 0;
	if (z1 == 0)
		pressure = 0;
	else
	 pressure = x * (z2/z1 - 1);
	return pressure;
}


void init() {
		//Setup LCD and 'blow' first bubble
	//Setup external SDRAM. Used for Frame Buffer
	sdramInit();	
	
	//Setup LPC2478 LCD Controller for our specific LCD
	//lcd_config is defined in lcd/lcd_cfg.h
	lcdInit(&lcd_config); 
	
	//Turn the LCD on
	lcdTurnOn();
	//fill screen
	lcd_fillScreen(BLUE);

	//Setup touchscreen
	touch_init();
	//initClock();

	
	drawTime(getHour(), getMinute(), CLOCKX, CLOCKY, 
		CLOCKX + CLOCKWIDTH, CLOCKY + CLOCKHEIGHT);//render clock
	//oepn ADC
	initADC();
	
}


int main(void) {
	profile admin;
	char x=0,y=0,z1=0,z2=0;
	uint8_t update = 0;
	uint8_t hourNow = 0;
	float pressure = 0;
	char str[10];

	admin.name = "admin";
	admin.data = data;
	admin.useSensor = 0; //sensor is on						
	
	init();
	
	while (1) {
			
		//render important stuff
		PINSEL4  = ((PINSEL4 & 0xF0300000) | 0x014FFFFF);
		FIO0CLR = 0x1 << 22; //led ladder
		//Read in X and Y coordinates
		touch_read_xy(&x,&y);
		touch_read_z(&z1, &z2);
		
		//debugging
		pressure = getPressure(x, z1, z2);
		sprintf(str, "pressure %5d", (int)pressure);
		lcd_putString(120,300,(unsigned char *)str);
		sprintf(str, "x: %d y: %d", x, y);
		lcd_putString(120,310,(unsigned char *)str);
		sprintf(str, "seconds: %d", getSeconds());
		lcd_putString(120,290,(unsigned char *)str);
		
		//update time for this loop iteration
		//if (updateTime()) {
			drawTime(hourNow, getMinute(), CLOCKX, CLOCKY, 
			CLOCKX + CLOCKWIDTH, CLOCKY + CLOCKHEIGHT);//render clock
			hourNow = (hourNow + 1) % 24; //change to hourNow = getHour();
			update = true;
		//}
			
		PINSEL4  = ~((PINSEL4 & 0xF0300000) | 0x014FFFFF);
		FIO0SET = 0x1 << 22; //led ladder
		
		//automation part
		configureLadder(); //give control to ladder
		updateDevices(&admin, hourNow, update);
		update = false;	

		udelay(500000);
		
	}
}
