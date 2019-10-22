#include "math_stuff.h"

position calc_position(circle *A, circle *B, circle *C){

        point p_AB = point_AB(A,B,C);
        printf("=============================\n");
        point p_AC = point_AC(A,B,C);
        printf("=============================\n");
        point p_BC = point_BC(A,B,C);
        printf("=============================\n");

	position p;
	p.pos_A = p_AB;
	p.pos_B = p_AC;
	p.pos_C = p_BC;
	
        printf("Die drei Punkte sind:\n");
        printf("%f | %f\n",p_AB.x,p_AB.y);
        printf("%f | %f\n",p_AC.x,p_AC.y);
        printf("%f | %f\n",p_BC.x,p_BC.y);

	return p;
}

point point_AB(circle *A, circle *B, circle *C){

        A->tmp_P = (pow(A->radius,2)) - (pow(B->radius,2)) - (pow(A->point.x,2)) + (pow(B->point.x,2)) - (pow(A->point.y,2)) + (pow(B->point.y,2));
        A->tmp_s = (-1) * (B->point.x - A->point.x) / (B->point.y - A->point.y);
        A->tmp_q = (A->tmp_P - 2*(A->point.y)*(B->point.y - A->point.y)) / (2*(B->point.y - A->point.y));

        printf("A->P = %f\n",A->tmp_P);
        printf("A->s = %f\n",A->tmp_s);
        printf("A->q = %f\n",A->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*A->tmp_s*A->tmp_q) - (2*A->point.x)) / (1+ (pow(A->tmp_s,2)));
        q = ((pow(A->tmp_q,2)) + (pow(A->point.x,2)) - (pow(A->radius,2))) / (1 + (pow(A->tmp_s,2)));

        printf("p = %f\n",p);
        printf("q = %f\n",q);

        point p_AB = pq_equation(p,q);

        point x0,x1;
        x0.x = p_AB.x;
        x1.x = p_AB.y;

        //Y-Wert ausrechnen
        x0.y = (A->tmp_P - 2*x0.x*(B->point.x - A->point.x)) / (2* (B->point.y - A->point.y));
        x1.y = (A->tmp_P - 2*x1.x*(B->point.x - A->point.x)) / (2* (B->point.y - A->point.y));

        printf("p_AB: Die nullstellen sind\n");
        printf("( %f | %f )\n",x0.x,x0.y);
        printf("( %f | %f )\n",x1.x,x1.y);

        p_AB = determine_point_radius(C,x0,x1);
        printf("p_AB: ( %f | %f )\n",p_AB.x,p_AB.y);
	return p_AB;
}

point point_AC(circle *A, circle *B, circle *C){

        A->tmp_P = (pow(A->radius,2)) - (pow(C->radius,2)) - (pow(A->point.x,2)) + (pow(C->point.x,2)) - (pow(A->point.y,2)) + (pow(C->point.y,2));
        A->tmp_s = (-1) * (C->point.x - A->point.x) / (C->point.y - A->point.y);
        A->tmp_q = (A->tmp_P - 2*(A->point.y)*(C->point.y - A->point.y)) / (2*(C->point.y - A->point.y));

        printf("A->P = %f\n",A->tmp_P);
        printf("A->s = %f\n",A->tmp_s);
        printf("A->q = %f\n",A->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*A->tmp_s*A->tmp_q) - (2*A->point.x)) / (1+ (pow(A->tmp_s,2)));
        q = ((pow(A->tmp_q,2)) + (pow(A->point.x,2)) - (pow(A->radius,2))) / (1 + (pow(A->tmp_s,2)));

        printf("p = %f\n",p);
        printf("q = %f\n",q);

        point p_AC = pq_equation(p,q);

        point x0,x1;
        x0.x = p_AC.x;
        x1.x = p_AC.y;

        //Y-Wert ausrechnen
        x0.y = (A->tmp_P - 2*x0.x*(C->point.x - A->point.x)) / (2* (C->point.y - A->point.y));
        x1.y = (A->tmp_P - 2*x1.x*(C->point.x - A->point.x)) / (2* (C->point.y - A->point.y));

        printf("p_AC: Die nullstellen sind\n");
        printf("( %f | %f )\n",x0.x,x0.y);
        printf("( %f | %f )\n",x1.x,x1.y);

        p_AC = determine_point_radius(B,x0,x1);
        printf("p_AC: ( %f | %f )\n",p_AC.x,p_AC.y);
        return p_AC;
}

point point_BC(circle *A, circle *B, circle *C){

        B->tmp_P = (pow(B->radius,2)) - (pow(C->radius,2)) - (pow(B->point.x,2)) + (pow(C->point.x,2)) - (pow(B->point.y,2)) + (pow(C->point.y,2));
        B->tmp_s = (-1) * (C->point.x - B->point.x) / (C->point.y - B->point.y);
        B->tmp_q = (B->tmp_P - 2*(B->point.y)*(C->point.y - B->point.y)) / (2*(C->point.y - B->point.y));

        printf("B->P = %f\n",B->tmp_P);
        printf("B->s = %f\n",B->tmp_s);
        printf("B->q = %f\n",B->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*B->tmp_s*B->tmp_q) - (2*B->point.x)) / (1+ (pow(B->tmp_s,2)));
        q = ((pow(B->tmp_q,2)) + (pow(B->point.x,2)) - (pow(B->radius,2))) / (1 + (pow(B->tmp_s,2)));

        printf("p = %f\n",p);
        printf("q = %f\n",q);

        point p_BC = pq_equation(p,q);

        point x0,x1;
        x0.x = p_BC.x;
        x1.x = p_BC.y;

        //Y-Wert ausrechnen
        x0.y = (B->tmp_P - 2*x0.x*(C->point.x - B->point.x)) / (2* (C->point.y - B->point.y));
        x1.y = (B->tmp_P - 2*x1.x*(C->point.x - B->point.x)) / (2* (C->point.y - B->point.y));

        printf("p_BC: Die nullstellen sind\n");
        printf("( %f | %f )\n",x0.x,x0.y);
        printf("( %f | %f )\n",x1.x,x1.y);

        p_BC = determine_point_radius(A,x0,x1);
        printf("p_BC: ( %f | %f )\n",p_BC.x,p_BC.y);
        return p_BC;
}

point determine_point_radius(circle* circle, point x0, point x1){

	//Den Punkt bestimmen der in dem Kreis liegt
        double tmp = sqrt( pow((circle->point.x - x0.x),2) + pow((circle->point.y - x0.y),2) );

        if(tmp < circle->radius){
                printf("Punkt (%f|%f) liegt in dem Kreis\n",x0.x,x0.y);
		return x0;
        }else{
                tmp = sqrt( pow((circle->point.x - x1.x),2) + pow((circle->point.y - x1.y),2) );
               	if(tmp < circle->radius){
			printf("Punkt (%f|%f) liegt in dem Kreis C\n",x1.x,x1.y);
			return x1;
		}else{
			printf("ERROR: keine der beiden Punkte liegt in dem Kreis. -> Ist nicht möglich\n");
		}
        }
	x0.x = -123456;
	x0.y = -123456;
	return x0;
}

point pq_equation(double p, double q){

	point erg;
	//Diskriminante
	double D = ((p*p)/4) - q;
	printf("Diskriminante = %f\n",D);

	if(D > 0){
		//2 lösungen
		printf("Es gibt 2 Lösungen\n");
		erg.x = -p/2 + sqrt(((p*p)/4) - q); 
		erg.y = -p/2 - sqrt(((p*p)/4) - q);
		
		printf("x1 = %f\n",erg.x);
		printf("x2 = %f\n",erg.y);

	}else if(D == 0){
		//eine lösung
		printf("Es gibt 1 Lösung\n");
		erg.x = -p/2 + sqrt(((p*p)/4) - q);
		printf("x1 = %f\n",erg.x);

	}else{
		//komplexe Lösung
		printf("Es gibt keine Lösung\n");
		erg.x = -123456;
		erg.y = -123456;
	}
	return erg;
}
