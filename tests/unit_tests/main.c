#include <stdio.h>
#include <stdlib.h>
#include "math_stuff.h"
#include <assert.h>
#include <stdbool.h>

#define EPSILON (0.001)
#define COMPARE(a,b) ((abs(a-b) <= EPSILON) ? true : false)

void test_calc_position(void);
void test_pq_equation(void);
void test_determine_point_radius(void);


int main(void){

	printf("Unit test starts ...\n");
	test_pq_equation();
	test_determine_point_radius();
	test_calc_position();
	return 0;
}




void test_determine_point_radius(void){

	point m = {0, 0};
	circle c = {m, 10};

	//Untersuchende Punkte
	point a = {1, 7};
	point b = {100, 0};
	
	point erg = determine_point_radius(&c,a,b);
	assert(COMPARE(erg.x, 1) && COMPARE(erg.y, 7));
}

void test_calc_position(void){

        //Ein gemeinsamer Schnittpunkt	
	point p_A = {0, 0};
        point p_B = {4, 0};
        point p_C = {2, 2};

        circle c_A, c_B, c_C;

	c_A.point = p_A;
	c_A.radius = 2;

      	c_B.point = p_B;
	c_B.radius = 2;
	
        c_C.point = p_C;
	c_C.radius = 2;

        position erg = calc_position(&c_A, &c_B, &c_C);//Muss noch getrickst werden
	assert(COMPARE(erg.pos_A.x, 2.0) && COMPARE(erg.pos_A.y, 0.0));


	//Kein gemeinsamer Schnittpunkt
	p_A.x = 3; p_A.y = 3;
        p_B.x = 6; p_B.y = 2;
        p_C.x = 4; p_C.y = 5;

        c_A.point = p_A; c_A.radius = 2;
        c_B.point = p_B; c_B.radius = 2;
	c_C.point = p_C; c_C.radius = 2;

	erg = calc_position(&c_A, &c_B, &c_C);
	assert(COMPARE(erg.pos_A.x, 4.887298) && COMPARE(erg.pos_A.y, 3.661895));
        assert(COMPARE(erg.pos_B.x, 4.983239) && COMPARE(erg.pos_B.y, 3.258380));
        assert(COMPARE(erg.pos_C.x, 4.279423) && COMPARE(erg.pos_C.y, 3.019615));
}

void test_pq_equation(void){

	int p,q;
	double x1,x2;

	p = 3;
	q = 2;
	x1 = -1;
	x2 = -2;
	point erg = pq_equation(p,q);
        assert(COMPARE(erg.x,x1) && COMPARE(erg.y,x2));

	p = 4;
	q = 1;
	x1 = -0.267949;
	x2 = -3.732051;
	erg = pq_equation(p,q);
	assert(COMPARE(erg.x,x1) && COMPARE(erg.y,x2));

	p = -3;
        q = -9;
        x1 = 4.8541;
	x2 = -1.8541;
	erg = pq_equation(p,q);
	assert(COMPARE(erg.x,x1) && COMPARE(erg.y,x2));
}
