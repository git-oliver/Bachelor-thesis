#include <stdio.h>
#include <stdlib.h>
#include "math_stuff.h"


#define SUCCESS	(0)
#define FAILED 	(-1)

int test_calc_position(void);
int test_pq_equation(void);
int test_determine_point_radius(void);


int main(void){

	printf("Wir testn\n");
//	printf("Func calc_position: %d\n",test_calc_position());
//	printf("Func pq_equation: %d\n",test_pq_equation());
	printf("Func determine_point_radius: %d\n",test_determine_point_radius());



	return 0;
}




int test_determine_point_radius(void){

	point m = {0, 0};
	circle c = {m, 10};

	//Untersuchende Punkte
	point a = {1, 7};
	point b = {100, 0};
	
	if(determine_point_radius(&c,a,b).x == a.x){
		return SUCCESS;
	}
	return FAILED;
}

int test_calc_position(void){
	
	point p_A = {1, 8};
        point p_B = {0, 0};
        point p_C = {1, 3};

        circle c_A = {p_A, 5, 2, 4};
        circle c_B = {p_B, 9, 3, 4};
        circle c_C = {p_C, 1, 3, 4};

        position erg = calc_position(&c_A, &c_B, &c_C);
        printf("Ergebnis\n");
        printf("Punkt A: %f | %f\n",erg.pos_A.x, erg.pos_A.y);
        printf("Punkt B: %f | %f\n",erg.pos_B.x, erg.pos_B.y);
        printf("Punkt C: %f | %f\n",erg.pos_C.x, erg.pos_C.y);

        if(erg.pos_A.x == 123){
                if(erg.pos_A.y == 456){

                        if(erg.pos_B.x == 789){
                                if(erg.pos_B.y == 789){

                                        if(erg.pos_C.x == 789){
                                                if(erg.pos_C.y == 789){
							return SUCCESS;
                                                }
                                        }
                                }
                        }
                }
        }
	return FAILED;
}

int test_pq_equation(void){

        point erg = pq_equation(3,2);
        if(erg.x == -1){
                if(erg.y == -2){
                	return SUCCESS;
		}
        }
	return FAILED;
}



