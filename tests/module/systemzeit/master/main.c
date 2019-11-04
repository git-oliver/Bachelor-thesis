#include <stdio.h>
#include "xtimer.h"
#include "periph/gpio.h"

void init(void);

int main(void)
{
        init();
	xtimer_sleep(1);
	printf("Los gehts\n");
	gpio_toggle(GPIO_PIN(0,18));
	uint32_t systime = xtimer_now_usec();
	gpio_toggle(GPIO_PIN(0,18));

	while(1){}
}

void init(void){
        
	gpio_init(GPIO_PIN(0,18),GPIO_OUT);
	gpio_clear(GPIO_PIN(0,18));
}
