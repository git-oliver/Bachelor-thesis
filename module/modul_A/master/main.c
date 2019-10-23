#include <stdio.h>
#include "xtimer.h"
#include "periph/gpio.h"

void ISR_func(void *arg);
void init(void);

int main(void)
{
        init();
	printf("Los gehts\n");
	while(1){}
}

void init(void){
        
	gpio_init(GPIO_PIN(1,23),GPIO_IN);
        gpio_init_int(GPIO_PIN(1,23),GPIO_IN,GPIO_RISING,&ISR_func,NULL);
        gpio_irq_enable(GPIO_PIN(1,23));

	gpio_init(GPIO_PIN(0,18),GPIO_OUT);
	gpio_clear(GPIO_PIN(0,18));
}
void ISR_func(void *arg){
	
	gpio_toggle(GPIO_PIN(0,18));
	(void)arg;
}
