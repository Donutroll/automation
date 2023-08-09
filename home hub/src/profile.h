#include <stdint.h>

typedef struct{
	char* name;
	uint16_t* data;
	uint8_t useSensor;
} profile; 


typedef struct{
	int x;
	int y;
	int w;
	int h;
	unsigned char* name;
	char on;
	char bits;
} rect;
