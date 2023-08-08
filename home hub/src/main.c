#include "touch.h"
#include "lcd/lcd_hw.h"
#include "lcd/lcd_grph.h"
#include "lcd/lcd_cfg.h"
#include "lcd/sdram.h"
#include <stdio.h>
#include "timer.h"
#include <LPC23xx.H>
#include "automation.h"
#include "gui.h"

extern uint16_t data[];
#define true 1
#define false 0

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

	
	drawClock(getHour(), getMinute());
	draw_main();
	
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
	admin.useSensor = 1; //sensor is on						
	
	init();
	
	while (1) {
			
		//render important stuff
		PINSEL4 = ((PINSEL4 & 0xF0300000) | 0x014FFFFF);
		FIO0CLR = 0x1 << 22; //clear ladder enable
		
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
			drawClock(hourNow, getMinute());//render clock
			hourNow = (hourNow + 1) % 24; //change to hourNow = getHour();
			update = true;
		//}
			
		PINSEL4  = ~((PINSEL4 & 0xF0300000) | 0x014FFFFF);

		
		//automation part
		configureLadder(); //give control to ladder
		updateDevices(&admin, hourNow, update);
		update = false;	

		udelay(5000);
		
	}
}
