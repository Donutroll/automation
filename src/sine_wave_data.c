#include <stdint.h>

/*uint8_t Rlight_data[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

uint8_t Llight_data[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

uint8_t blinds_data[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

uint8_t sprinkler_data[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};*/

uint16_t data[] = {
	0, 0, 0, 0,  
	0, 0, 0, 0x3,
	0x3, 0x3, 0x3, 0x3, 
	0x3, 0x3, 0x3, 0x3,
	0x1F, 0x1F, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18
};

// 	| bit 5 		| bit 4	 | bit3 	| bit2 	 | bit1 	| bit0 	 |
//  | sprinkler | light2 | light1 | blind3 | blind2 | blind1 |
