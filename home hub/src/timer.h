#include <stdint.h>

void udelay(unsigned int delay_in_us);
uint8_t getMinute(void);
uint8_t getHour(void);
uint8_t getSeconds(void);
void initClock(void);
int updateTime(void);

