#include "lpc24xx.h"
#include <stdint.h>
#include "lcd/lcd_grph.h"
#define BORDER 2
#define THICKNESS 1

//ordering of function calls
//   -	1
// 4| |5
//   -3
// 6| |7
//   - 2

void drawNum(unsigned short num, unsigned short x1, unsigned short y1, unsigned short x2, 
unsigned short y2, unsigned int border, unsigned int thickness, unsigned short colour) {
	
	unsigned short _x1 = x1 + border;
	unsigned short _y1 = y1 + border;
	unsigned short _x2 = x2 - border;
	unsigned short _y2 = y2 - border;
	unsigned short width = _x2 - _x1;
	unsigned short height = _y2 - _y1;

	if (num == 0) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x1, _y1 + border + thickness + height/2 , _x1 + thickness, _y2 - border - thickness, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 1) {
			//vertical
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 2) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x1, _y1 + border + thickness + height/2 , _x1 + thickness, _y2 - border - thickness, colour);
	}
	if (num == 3) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 4) {
			//horizontal
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 5) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 6) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x1, _y1 + border + thickness + height/2 , _x1 + thickness, _y2 - border - thickness, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 7) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);

			
			//vertical
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}
	if (num == 8) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness,colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x1, _y1 + border + thickness + height/2 , _x1 + thickness, _y2 - border - thickness, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness,colour);
	}
	if (num == 9) {
			//horizontal
			lcd_fillRect(_x1, _y1, _x2, _y1 + thickness, colour);
			lcd_fillRect(_x1, _y2 - thickness, _x2, _y2, colour);
			lcd_fillRect(_x1, _y1 + (height - thickness)/2, _x2, _y1 + height/2 + thickness, colour);
			
			//vertical
			lcd_fillRect(_x1, _y1 + border + thickness, _x1 + thickness, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness, _x2, _y1 + (height - thickness)/2 - border, colour);
			lcd_fillRect(_x2 - thickness, _y1 + border + thickness + height/2, _x2,  _y2 - border - thickness, colour);
	}

		
}


void drawTime(unsigned short hour, unsigned short minute, unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2) {
	
	unsigned short width = x2 - x1;
	unsigned short height = y2 - y1;
	unsigned short part = width - 2*BORDER;
	
	unsigned short part2 = x1 + part/4;				//ones
	unsigned short part3 = x1 + part*2/4;			//divider
	unsigned short part4 = x1 + part*2/4 + 2*BORDER; //tens
	unsigned short part5 = x1 + part*3/4 + 2*BORDER; //ones
	
	
	unsigned short hour1 = (hour / 10) % 10;
	unsigned short hour2 = hour % 10;
	unsigned short minute1 = (minute / 10) % 10;
	unsigned short minute2 = minute % 10;
	
	/*//guide lines
	//hour
	lcd_drawRect(x1, y1, part2, y2, WHITE);
	lcd_drawRect(part2, y1, part3, y2, WHITE);
	//divider
	lcd_drawRect(part3, y1, part4, y2, WHITE);
	//minute
	lcd_drawRect(part4, y1, part5, y2, WHITE);
	lcd_drawRect(part5, y1, x2, y2, WHITE);*/
	
	//reset
	lcd_fillRect(x1, y1, x2, y2, BLACK);
	
	//draw dividing circles
	lcd_fillcircle(part3 + BORDER, y1 + height/4, 2, WHITE);
	lcd_fillcircle(part3 + BORDER, y1 + height*3/4, 2, WHITE);
	
	
	
	drawNum(hour1, x1, y1, part2, y2, BORDER, THICKNESS, WHITE); 
	drawNum(hour2, part2, y1, part3, y2, BORDER, THICKNESS, WHITE);
	drawNum(minute1, part4, y1, part5, y2, BORDER, THICKNESS, WHITE);
	drawNum(minute2, part5, y1, x2, y2, BORDER, THICKNESS, WHITE);

}
