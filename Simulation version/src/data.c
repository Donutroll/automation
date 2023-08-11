#include <stdint.h>

//stores the automation data of each hour, light bits are unused since sensor is always on
//blinds are open where 1 and closed where 0
//lights are open where 1 and closed where 0
//sprinklers are open where 1 and closed where 0
uint16_t data[] = {
	0, 0, 0, 0,  
	0, 0, 0, 0x7,
	0x7, 0x7, 0x7, 0x7, 
	0x7, 0x7, 0x7, 0x7,
	0x2F, 0x2F, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18
};

// 	| bit 5 		| bit 4	 | bit3 	| bit2 	 | bit1 	| bit0 	 |
//  | sprinkler | light2 | light1 | blind3 | blind2 | blind1 |



	