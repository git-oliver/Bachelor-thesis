#include "xtimer.h"
#include "periph/gpio.h"
#include <stdio.h>

void init(void);

int main(void)
{
	init();
	
	printf("Los gehts\n");
	xtimer_sleep(5);
        
	gpio_set(GPIO_PIN(0,5));
        xtimer_usleep(40000);
        gpio_clear(GPIO_PIN(0,5));

	while(1){}
}
void init(void){

	gpio_init(GPIO_PIN(0,5),GPIO_OUT);
        gpio_clear(GPIO_PIN(0,5));
}
