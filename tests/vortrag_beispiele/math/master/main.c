#include "../include.h"
#include <stdio.h>
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include <inttypes.h>
#include <math.h>
#include "math_stuff.h"

int main(void)
{
	xtimer_sleep(1);
	
	int a_x,a_y,a_radius;
	int b_x,b_y,b_radius;
	int c_x,c_y,c_radius;

        circle c_A, c_B, c_C;
	position p;

	a_x = 0; a_y = 0; a_radius = 2;
	b_x = 4; b_y = 0; b_radius = 2;
	c_x = 2; c_y = 2; c_radius = 2;
	
	c_A.point.x = a_x;
        c_A.point.y = a_y;
	c_A.radius = a_radius;

	c_B.point.x = b_x;
        c_B.point.y = b_y;
        c_B.radius = b_radius;

	c_C.point.x = c_x;
        c_C.point.y = c_y;
        c_C.radius = c_radius;

	p = calc_position(&c_A, &c_B, &c_C);
        printf("======================================================\n");
        printf("Punkt A: (%d | %d) r = %d\n",a_x,a_y,a_radius);
        printf("Punkt B: (%d | %d) r = %d\n",b_x,b_y,b_radius);
        printf("Punkt C: (%d | %d) r = %d\n",c_x,c_y,c_radius);
        printf("Ergebnis:\n");
        printf("Erfolgreich: %s\n",p.success ? "true":"false");
        printf("Punkt 1: (%f | %f)\n",p.pos_A.x,p.pos_A.y);
        printf("Punkt 2: (%f | %f)\n",p.pos_B.x,p.pos_B.y);
        printf("Punkt 3: (%f | %f)\n",p.pos_C.x,p.pos_C.y);
	printf("\n\n\n\n\n");








	a_x = 0; a_y = 0; a_radius = 2;
        b_x = 4; b_y = 0; b_radius = 3;
        c_x = 2; c_y = 2; c_radius = 2;

	c_A.point.x = a_x;
        c_A.point.y = a_y;
        c_A.radius = a_radius;

	c_B.point.x = b_x;
        c_B.point.y = b_y;
        c_B.radius = b_radius;

	c_C.point.x = c_x;
        c_C.point.y = c_y;
        c_C.radius = c_radius;

	p = calc_position(&c_A, &c_B, &c_C);
	printf("======================================================\n");
        printf("Punkt A: (%d | %d) r = %d\n",a_x,a_y,a_radius);
        printf("Punkt B: (%d | %d) r = %d\n",b_x,b_y,b_radius);
        printf("Punkt C: (%d | %d) r = %d\n",c_x,c_y,c_radius);
        printf("Ergebnis:\n");
        printf("Erfolgreich: %s\n",p.success ? "true":"false");
	printf("Punkt 1: (%f | %f)\n",p.pos_A.x,p.pos_A.y);
        printf("Punkt 2: (%f | %f)\n",p.pos_B.x,p.pos_B.y);
        printf("Punkt 3: (%f | %f)\n",p.pos_C.x,p.pos_C.y);	
	printf("\n\n\n\n\n");







        
	a_x = 0; a_y = 0; a_radius = 2;
        b_x = 4; b_y = 0; b_radius = 3;
        c_x = 10; c_y = 10; c_radius = 2;

        c_A.point.x = a_x;
        c_A.point.y = a_y;
        c_A.radius = a_radius;

        c_B.point.x = b_x;
        c_B.point.y = b_y;
        c_B.radius = b_radius;

        c_C.point.x = c_x;
        c_C.point.y = c_y;
        c_C.radius = c_radius;

        p = calc_position(&c_A, &c_B, &c_C);
        printf("======================================================\n");
        printf("Punkt A: (%d | %d) r = %d\n",a_x,a_y,a_radius);
        printf("Punkt B: (%d | %d) r = %d\n",b_x,b_y,b_radius);
        printf("Punkt C: (%d | %d) r = %d\n",c_x,c_y,c_radius);
        printf("Ergebnis:\n");
        printf("Erfolgreich: %s\n",p.success ? "true":"false");
        printf("Punkt 1: (%f | %f)\n",p.pos_A.x,p.pos_A.y);
        printf("Punkt 2: (%f | %f)\n",p.pos_B.x,p.pos_B.y);
        printf("Punkt 3: (%f | %f)\n",p.pos_C.x,p.pos_C.y); 






	return 0;
}
