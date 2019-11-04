#ifndef MATH_STUFF_H
#define MATH_STUFF_H

#include <stdio.h>
#include <math.h>

typedef struct{
        double x;
        double y;
}point;

typedef struct{
        point point;
        double radius;

	double t_prop;
	double omega;
}circle;

typedef struct{
	point pos_A;
	point pos_B;
	point pos_C;
}position;

position calc_position(circle *A, circle *B, circle *C);
point pq_equation(double p, double q);
point determine_point_radius(circle* circle, point x0, point x1);
point point_AB(circle *A, circle *B, circle *C);
point point_AC(circle *A, circle *B, circle *C);
point point_BC(circle *A, circle *B, circle *C);



#endif
