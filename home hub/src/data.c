#include <stdint.h>

uint16_t data[] = {
	0x3F, 0x1, 0x3F, 0xF, 
	0x1F, 0x3F, 0x1F, 0xF,
0x7, 0x3, 0x1, 0xF, 
	0x1F, 0x3F, 0x1F, 0xF,
 0x7, 0x3, 0x1, 0xF, 
	0x3F, 0xF, 0x7, 0x3
};

// 	| bit 5 		| bit 4	 | bit3 	| bit2 	 | bit1 	| bit0 	 |
//  | sprinkler | light2 | light1 | blind3 | blind2 | blind1 |

/*
	default
	0x0, 0, 0, 0,  
	0, 0, 0, 0x3,
	0x3, 0x3, 0x3, 0x3, 
	0x3, 0x3, 0x3, 0x3,
	0x1F, 0x1F, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18

*/

/* 
	test data
	0x1F, 0x1F, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18,
	0, 0, 0, 0,  
	0, 0, 0, 0x0,
	0x3, 0x3, 0x3, 0x3, 
	0x3, 0x3, 0x3, 0x3
	*/
	