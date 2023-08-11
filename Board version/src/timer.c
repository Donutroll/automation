#include "lpc24xx.h"
#include <stdint.h>
#include "lcd/lcd_grph.h"
#include "drawTime.h"
#define U_CLK 71 //clkspd in us

static uint8_t hour = 0;
static uint8_t minute = 0;
static uint8_t seconds = 0;

uint8_t getHour() {
	return hour;
}

uint8_t getMinute() {
	return minute;
}

uint8_t getSeconds() {
	return seconds;
}

void udelay(unsigned int delay_in_us) {

	T0PR = U_CLK;
	T0MCR = 0x6; //enable and reset timer on match
	T0MR0 = delay_in_us;	//set match register
	T0TCR = 0x1; //enable timer
	
	while ((T0TCR & 0x1)); //wait for done
		
}
	

void initClock() {
	PCONP |= 0x1 << 9; //enable RTC
	RTC_CCR = 0x0;		//disable clock
	RTC_CCR = 0x12;		//reset clock
	RTC_CCR = 0x11;		//enable clock
}

//return if the peripherals need to be updated
int updateTime() {
		seconds = RTC_CTIME0 & 0x2F; //update time

		if (minute != (RTC_CTIME0 & 0xFF << 8) >> 8 || //check if clock needs to be updated
			hour != (RTC_CTIME0 & 0xFF << 16) >> 16) {
				minute = (RTC_CTIME0 & 0xFF << 8) >> 8; 
				hour = (RTC_CTIME0 & 0xFF << 16) >> 16;
				return 1;
			}
	return 0;
}


	





