
#include "touch.h"
#include <stdint.h>

#include "lpc24xx.h"
#include "delay.h"
#include "lcd/lcd_hw.h"
#include "lcd/lcd_grph.h"
#include "lcd/lcd_cfg.h"
#include "lcd/sdram.h"

#include "stdio.h"

void draw_main(void) {
	int i;
	int rect_width = 180;
	int rect_height = 50;
	int vert_space = 22;
	int horz_space = 30;

	lcd_line(0, 80, 240, 80, BLACK);

	lcd_drawRect(20, 10, 80, 70, BLACK);
	
	lcd_drawRect(90, 10, 150, 70, BLACK);
	
	lcd_drawRect(160, 10, 220, 70, BLACK);
	
	lcd_putString(35, 30, "Owner");
	
	lcd_putString(110, 30, "User");
	
	lcd_putString(170, 30, "Settings");
	
	lcd_putString(100, 90, "Lights");
	lcd_line(25, 95, 95, 95, BLACK);
	lcd_line(25, 95, 25, 157, BLACK);
	
	lcd_line(215, 95, 140, 95, BLACK);
	lcd_line(215, 95, 215, 157, BLACK);
	
	lcd_line(25, 157, 215, 157, BLACK);
	
	lcd_putString(100, 164, "Blinds");
	lcd_line(25, 167, 95, 167, BLACK);
	lcd_line(25, 167, 25, 229, BLACK);
	
	lcd_line(215, 167, 140, 167, BLACK);
	lcd_line(215, 167, 215, 229, BLACK);
	
	lcd_line(25, 229, 215, 229, BLACK);	
	
	
	lcd_putString(94, 237, "Sprinkler");
	lcd_line(25, 241, 90, 241, BLACK);
	lcd_line(25, 241, 25, 301, BLACK);
	
	lcd_line(215, 241, 150, 241, BLACK);
	lcd_line(215, 241, 215, 301, BLACK);
	
	lcd_line(25, 301, 215, 301, BLACK);	
	
	return;
}


int password(int x ,int y, int guesses, int current_screen[5]) {
	int i = 0;
	int rect_width = 60;
	int rect_height = 50;
	int vert_space = 8;
	int horz_space = 15;
	int row = 0;
	int column = 0;
	int keypad[4][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7 , 8, 9},
		{0, 0, 0}
	};
	int pass_code[4] = {1,2,3,4};
	int guess[4];
	char str[10];
	
 	lcd_drawRect(35, 40, 205, 70, BLACK);

	lcd_putString(55, 20, "Please input Password");

	//lcd_putString(55, 100, "Please ");
	
	while (row <= 3) {
		
		while (column <=2) {
			
			lcd_drawRect(horz_space + column*(rect_width + horz_space), 
			
			80 + row*(vert_space + rect_height),
			
			(horz_space + rect_width)*(column+1),
			
			80 + rect_height + row*(vert_space + rect_height), 
			
			BLACK
			);
			
			if (x >= horz_space + column*(rect_width + horz_space) && 
				x <= (horz_space + rect_width)*(column+1)) {
				if (y >= 80 + row*(vert_space + rect_height) && 
					y <= 80 + rect_height + row*(vert_space + rect_height)){
						if (guesses <= 3) {
// 							sprintf(str, "pressure: %d", guesses);
// 							lcd_putString(10, 10, str);							

							guess[guesses] = keypad[row][column];
							guesses++;
							mdelay(10);
						}


				}
			}
			
			column ++;
		}
		
		column = 0;
		
		
		row++;
	}
	
	for (i = 0; i <= guesses; i++) {
		//lcd_fillcircle(55+i*20, 60, 7, BLACK);
		lcd_fillRect(70+i*30,45,85+i*30,60,BLACK);
	}
	if (guesses >= 3) {
			current_screen[0] = 1;
			current_screen[4] = 0;
			lcd_fillScreen(WHITE);
	}
	
	
	return(guesses);
}


int time_set(int x,  int y) {
	
	
	
	
	
	lcd_fillScreen(WHITE);
	
	lcd_drawRect(90, 10, 150, 70, BLACK);
	
	
	
	
}


int main_screen(int x ,int y, int automatic, int rect_perim[][7], int current_screen[5]){

	//bit 0 contains automation flag, bit 1 is manual flag, bit 2~7 are control flags
	uint8_t control = 0;
	for (i = 0; i <= 2; i++) {
		rect_perim[i][0] = horz_space;
		rect_perim[i][1] = 80+vert_space+i*(rect_height+vert_space);
		rect_perim[i][2] = horz_space + rect_width;
		rect_perim[i][3] = 80+vert_space+rect_height+i*(rect_height+vert_space);
		

		if (x >= rect_perim[i][0] && x <= rect_perim[i][2]) {
			if (y >= rect_perim[i][1] && y <= rect_perim[i][3]) {
				
				if (automatic == 1) {

				} else if (automatic == 0) {
					rect_perim[i][5] = !rect_perim[i][5];
					
				}
				
			}

		}
		lcd_fillRect(rect_perim[i][0], rect_perim[i][1],
		rect_perim[i][2], rect_perim[i][3], rect_perim[i][4]);
	}
	//Owner 20, 10, 80, 70
	if (x >= 20 && x <= 80) {
		if (y >= 10 && y <= 70) {
			current_screen[0] = 0;
			current_screen[1] = 0;
			current_screen[2] = 0;
			current_screen[3] = 0;
			current_screen[4] = 1;
			lcd_fillScreen(WHITE);
		}
	}	
	
	//User 90, 10, 150, 70
	if (x >= 90 && x <= 150) {
		if (y >= 10 && y <= 70) {
			current_screen[0] = 0;
			current_screen[1] = 1;
			current_screen[2] = 0;
			current_screen[3] = 0;
			current_screen[4] = 0;
			lcd_fillScreen(WHITE);
		}
	}
	
	
	//Settings
	if (x >= 160 && x <= 220) {
		if (y >= 10 && y <= 70) {
			current_screen[0] = 0;
			current_screen[1] = 0;
			current_screen[2] = 1;
			current_screen[3] = 0;
			current_screen[4] = 0;
			lcd_fillScreen(WHITE);
		}
	}
	
	return;
}





int render_screen(void) {
	char x=0, y=0;
	char z1 = 0;
	char z2 = 0;
	int threshold = 2;
	int pressure = 0;
	char str[10];
	int colour = DARK_GRAY;
	int point_x;
	int point_y;
	int automatic = 0;
	int rect_perim[3][7];
	int guesses = 0;
	int current_screen[5]; //Main screen, user, settings, password, owner
	current_screen[0] = 1;
	current_screen[1] = 0;
	current_screen[2] = 0;
	current_screen[3] = 0;
	current_screen[4] = 0;
	
	

	rect_perim[0][4] = colour; //lights
	rect_perim[1][4] = colour; // blinds
	rect_perim[2][4] = colour; // sprinkler
	
	rect_perim[0][5] = 0; //lights
	rect_perim[1][5] = 0; // blinds
	rect_perim[2][5] = 0; // sprinkler	
	

	
	//Setup touchscreen
	touch_init();
	
	//Setup external SDRAM. Used for Frame Buffer
	sdramInit();	
	
	//Setup LPC2478 LCD Controller for our specific LCD
	//lcd_config is defined in lcd/lcd_cfg.h
	lcdInit(&lcd_config); 
	
	//Turn the LCD on
	lcdTurnOn();	
	
	lcd_fillScreen(WHITE);
	
	
	//Loop forever
	while (1) {
		
		
		//Read in X and Y coordinates
		touch_read_xy(&x,&y);
		point_x = x*240/255;
		point_y = y*320/255;		
		//password(x, y);
		
		if (current_screen[0] == 1) {
			main_screen(point_x, point_y, automatic, rect_perim, current_screen);
			
		} else if (current_screen[1] == 1) {
			
			//user
		} else if (current_screen[2] == 1) {
			//settings
		}	else if (current_screen[3] == 1) {
			//password
		}	else if (current_screen[4] == 1) {
			mdelay(10);
			guesses = password(x,y,guesses, current_screen);
			
		}
		
		if (rect_perim[0][5] == 1) {
			rect_perim[0][4] = LIGHT_GRAY;
			
		} else {
			rect_perim[0][4] = DARK_GRAY;
		}
		
		read_pressure(&z1, &z2);
		
		pressure = (4096*z1)/(x*(z2-z1));
		
		//sprintf(str, "pressure: %d", pressure);
		//lcd_putString(10, 10, str);
		
		if (pressure >= threshold) {
				
				//React to button pushed
		}
		

		

	}
}



