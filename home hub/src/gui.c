
#include "touch.h"
#include <stdint.h>
#include "timer.h"
#include "lpc24xx.h"
#include "delay.h"
#include "lcd/lcd_hw.h"
#include "lcd/lcd_grph.h"
#include "lcd/lcd_cfg.h"
#include "lcd/sdram.h"
#include "profile.h"
#include "stdio.h"
#include "drawTime.h"

#define CLOCKX 50
#define CLOCKY 30
#define CLOCKWIDTH  100   //60
#define CLOCKHEIGHT 40    //27

#define COLOR 0xFFFF
#define true 1
#define false 0

#define xMax 	240
#define yMax 320

profile admin;
rect Screen;
rect Clock;
rect buttons;
rect settings;
rect lightbut;
rect blindsbut;
rect sprinklerbut;
rect manualbut;
extern uint16_t data[];

void drawClock(int hour, int minute) {
	drawTime(hour, minute, Clock.x, Clock.y, 
		Clock.x + Clock.w, Clock.y + Clock.h);//render clock
}

float getPressure(int x, int z1, int z2) {
	float pressure = 0;
	if (z1 == 0)
		pressure = 0;
	else
	 pressure = x * (z2/z1 - 1);
	return pressure;
}


void drawRect(rect R, lcd_color_t c) {
	lcd_drawRect(R.x, R.y, R.x+R.w, R.y + R.h, c);
}


void drawButton(rect R,  lcd_color_t c) {
	drawRect(R,c);
	lcd_putString(R.x + R.w/3, R.y + R.h/2, R.name);
}

int isPressed(rect R, char x, char y) {
	if (x >= R.x && x <= (R.x + R.w) && y >= R.y && y <= (R.y + R.h)){
		udelay(500);
		if (x >= R.x && x <= (R.x + R.w) //double check condition
			&& y >= R.y && y <= (R.y + R.h))
					return true;
	}
	
	return false;
}


void triggerButton(rect *R) {
			if (R->on == false){
				R->on = true;
			drawButton(*R, GREEN);
			}
			else {
				R->on = false;
			drawButton(*R, WHITE);
			}
}


void setScreen(void) {
	
	Screen.x = 0;
	Screen.y = 0;
	Screen.w = xMax;
	Screen.h = yMax;
	
	Clock.x = 0;
	Clock.y = 0;
	Clock.w = Screen.w;
	Clock.h = Screen.h/4 - 10;
	
	buttons.x = 0;
	buttons.y = Screen.h/4;
	buttons.w = Screen.w/2;
	buttons.h = Screen.h - Clock.h;
	
	
	settings.x = Screen.w/2;
	settings.y = Screen.h/4;
	settings.w = Screen.w/2;
	settings.h = Screen.h - Clock.h;
	
	//manual buttons
	lightbut.x = buttons.x;
	lightbut.y = buttons.y;
	lightbut.w = buttons.w;
	lightbut.h = buttons.h/3;
	lightbut.name = "lights";
	lightbut.on = false;
	
	blindsbut.x = buttons.x;
	blindsbut.y = lightbut.y + lightbut.h;
	blindsbut.w = buttons.w;
	blindsbut.h = buttons.h/3;
	blindsbut.name = "blinds";			
	blindsbut.on = false;
	
	sprinklerbut.x = buttons.x;
	sprinklerbut.y = blindsbut.y + blindsbut.h;
	sprinklerbut.w = buttons.w;
	sprinklerbut.h = buttons.h/3;
	sprinklerbut.name = "sprinklers";
	sprinklerbut.on = false;
	
	
	//setting buttons
	manualbut.x = settings.x;
	manualbut.y = settings.y;
	manualbut.w = settings.w;
	manualbut.h = settings.h/3;
	manualbut.name = "manual";
	manualbut.on = false;
	
	admin.name = "admin";
	admin.data = data;
	admin.useSensor = 0;							

	drawRect(Screen, COLOR);
	drawRect(Clock, COLOR);
	drawRect(buttons, COLOR);
	drawRect(settings, COLOR);
	drawButton(lightbut, COLOR);
	drawButton(blindsbut, COLOR);
	drawButton(sprinklerbut, COLOR);
	drawButton(manualbut, COLOR);
}


void handleButtons(char *manual_state, int x, int y){

if (manualbut.on) {
		if (isPressed(lightbut, x,y)) {
				if (lightbut.on == false) { //set lights state
					*manual_state |= 0x3 << 3;
					lightbut.on = true;
					drawButton(lightbut, GREEN);
				}
				else if (lightbut.on == true) {
					*manual_state &= ~(0x3 <<3);
					lightbut.on = false;
					drawButton(lightbut, WHITE);
				}
				
		}
		else if (isPressed(sprinklerbut, x,y)) {
				if (sprinklerbut.on == false) { //set sprinkler state
					*manual_state |= 0x1 << 5;
					sprinklerbut.on = true;
					drawButton(sprinklerbut, GREEN);
				}
				else if (sprinklerbut.on == true) {
					*manual_state &= ~(0x1 << 5);
					sprinklerbut.on = false;
					drawButton(sprinklerbut, WHITE);
				}
			}
		else if (isPressed(blindsbut, x,y)) {
				if (blindsbut.on == false) { //set blind state
					*manual_state |= 0x7;
					blindsbut.on = true;
					drawButton(blindsbut, GREEN);
				}
				else if (blindsbut.on == true) {
					*manual_state &= ~(0x7);
					blindsbut.on = false;
					drawButton(blindsbut, WHITE);
				}
		}
	}
	
			if (isPressed(manualbut, x, y)) {
				if (manualbut.on == false) { //
					manualbut.on = true;
					drawButton(manualbut, GREEN);
				}
				else if (manualbut.on == true) {
					manualbut.on = false;
					*manual_state = 0;
					drawButton(manualbut, WHITE);
					
					//reset all buttons
					blindsbut.on = false;
					drawButton(blindsbut, WHITE);
					sprinklerbut.on = false;
					drawButton(sprinklerbut, WHITE);
					lightbut.on = false;
					drawButton(lightbut, WHITE);
	
				}
		}
		
}




