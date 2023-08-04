#include "bubbles.h"
#include "touch.h"
#include "lcd/lcd_hw.h"
#include "lcd/lcd_grph.h"
#include "lcd/lcd_cfg.h"
#include "lcd/sdram.h"
#include <stdio.h>
#include "drawTime.h"
#include "timer.h"


float getPressure(int x, int z1, int z2) {
	char str[10];
	float pressure = 0;
	if (z1 == 0)
		pressure = 0;
	else
	 pressure = x * (z2/z1 - 1);
	sprintf(str, "pressure %5d", (int)pressure);
	lcd_putString(10,10,(unsigned char *)str);
	return pressure;
}


int main(void) {
	char x=0, y=0, z1=0, z2=0;
	float pressure = 0;
	//Setup LCD and 'blow' first bubble
	//Setup external SDRAM. Used for Frame Buffer
	sdramInit();	
	
	//Setup LPC2478 LCD Controller for our specific LCD
	//lcd_config is defined in lcd/lcd_cfg.h
	//lcdInit(&lcd_config); 
	
	//Turn the LCD on
	//lcdTurnOn();
	
	//fill screen
	//lcd_fillScreen(BLACK);

	//Setup touchscreen
	touch_init();
	initClock();
	
	//Loop forever
	while (1) {
		//Read in X and Y coordinates
		//touch_read_xy(&x,&y);
		//touch_read_z(&z1, &z2);
		//pressure = getPressure(x, z1, z2);
	}
}
