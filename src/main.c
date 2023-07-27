#include "lpc24xx.h"
#include <stdint.h>
#include "profile.h"
#include "timer.h"
#include "automation.h"

extern uint8_t Rlight_data[];
extern uint8_t Llight_data[];

#define minute time & 0x1F
#define hour time << 6
 


void init() {
	
	//system clock
	initClock();
	
	//ADC
	
	//set output
	FIO0DIR |= 0x1 << 22;	//ladder enable
	FIO2DIR |= 0xFF << 1; //ladder leds
	FIO3DIR |= 0x3F << 16; //RGB leds
	
	//enable
	FIO0SET = 0x1 << 22; //ladder
	
}


int main(void) {
	
	profile main;
	uint8_t states = 0;
	uint8_t prevHour = 100;
	float sensorVal = 0;
	
	main.name = "user";
	main.Rlight = Rlight_data;
	main.Llight = Llight_data;
	
	init();
	
	while(1) {
		if (prevHour != getHour()) {
			prevHour = getHour();
			setDevices(main, states);
		}
		sensorVal = readSensor();
		
	}
	return 0;
}
