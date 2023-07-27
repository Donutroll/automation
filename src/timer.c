#include "lpc24xx.h"
#include <stdint.h>

#define U_CLK 71 //clkspd in us
#define minute time & 0x2F
#define hour time >> 6


static volatile uint16_t time; //bits 0~5 hold minute, 6~10 hold hour

uint16_t getHour() {
	return hour;
}

uint16_t getMinute() {
	return minute;
}

void udelay(unsigned int delay_in_us) {

	T0PR = U_CLK;
	T0MCR = 0x6; //enable and reset timer on match
	T0MR0 = delay_in_us;	//set match register
	T0TCR = 0x1; //enable timer
	
	while ((T0TCR & 0x1)); //wait for done
		
}


__irq void updateTime() {
	++time;
	
	if (minute >= 60) 
		time = (hour + 1) << 6; //reset minute, add hour
	if (hour >= 24)
		time = 0;
	
	T1IR = 0; //reset interrupt
}
	

void initClock() {
	T1PR = 72000000 - 1;
	T1MR0 = 1;
	
	T1TCR = 0x1; //enable timer
	VICVectAddr5 = (unsigned) updateTime;
	VICIntEnable = 0x1 << 5; //enable timer1 interrupt
	T1MCR = 0x3; //generate interrupt and reset CLK on match
	
}

