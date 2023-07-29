#include <stdint.h>

typedef struct{
	char* name;
	
	/*uint8_t* Rlight;
	uint8_t* Llight;
	
	//not finalised
	uint32_t* blinds;
	uint8_t* sprinkler;*/
	
	uint16_t* data;
	uint8_t useSensor;
} profile; 
