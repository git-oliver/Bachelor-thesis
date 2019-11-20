#ifndef MATH_STUFF_H
#define MATH_STUFF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


typedef struct{
        double x;
        double y;
}point;

typedef struct{
        point point;
        double radius;

	double t_prop;
	double omega;
	
	double tmp_P;
	double tmp_s;
	double tmp_q;
}circle;

typedef struct{
	point pos_A;
	point pos_B;
	point pos_C;
	bool success;
}position;

typedef struct{
	point a;
	point b;
	bool success;
}CircleIntersection;


position calc_position(circle *A, circle *B, circle *C);
point pq_equation(double p, double q);
point determine_point_radius(circle* circle, point x0, point x1);
point point_AB(circle *A, circle *B, circle *C);
point point_AC(circle *A, circle *B, circle *C);
point point_BC(circle *A, circle *B, circle *C);
CircleIntersection getIntersection(circle *A, circle *B);

#endif
