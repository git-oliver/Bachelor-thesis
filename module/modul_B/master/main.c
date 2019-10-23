#include <stdio.h>
#include "xtimer.h"
#include "periph/gpio.h"

void init(void);

int main(void)
{
        init();
	printf("Los gehts\n");

	gpio_set(GPIO_PIN(0,18));
	xtimer_sleep(1);
        gpio_clear(GPIO_PIN(0,18));

	while(1){}
}

void init(void){
        
	gpio_init(GPIO_PIN(0,18),GPIO_OUT);
	gpio_clear(GPIO_PIN(0,18));
}
