#include "math_stuff.h"

#define EPSILON (0.001)
#define COMPARE(a,b) ((abs(a-b) <= EPSILON) ? true : false)

position calc_position(circle *A, circle *B, circle *C){

	CircleIntersection intersection;
	point p;
        position prime_position;
        prime_position.success = false;

	//Schnittpunkt von A und B
	intersection = getIntersection(A,B);
	if(intersection.success){
		p = determine_point_radius(C, intersection.a, intersection.b);
		prime_position.pos_C = p;
	}else{
		return prime_position;
	}
        
	//Schnittpunkt von A und C
        intersection = getIntersection(A,C);
        if(intersection.success){

		//printf("Kreis B: x: %f   y: %f\n",B->point.x, B->point.y);
	        //printf("Punkt A: x: %f  y: %f\n",intersection.a.x,intersection.a.y);
        	//printf("Punkt B: x: %f  y: %f\n",intersection.b.x,intersection.b.y);

                p = determine_point_radius(B, intersection.a, intersection.b);
                prime_position.pos_B = p;
        }else{
                return prime_position;
        }
        
	//Schnittpunkt von B und C
        intersection = getIntersection(B,C);
        if(intersection.success){
                p = determine_point_radius(A, intersection.a, intersection.b);
                prime_position.pos_A = p;
        }else{
                return prime_position;
        }

	prime_position.success = true;
	return prime_position;

	//////////////////////////////////////////////////
/*
        point p_AB = point_AB(A,B,C);
        //printf("=============================\n");
        point p_AC = point_AC(A,B,C);
        //printf("=============================\n");
        point p_BC = point_BC(A,B,C);
        //printf("=============================\n");

	position p;
	p.pos_A = p_AB;
	p.pos_B = p_AC;
	p.pos_C = p_BC;
	
        //printf("Die drei Punkte sind:\n");
        //printf("%f | %f\n",p_AB.x,p_AB.y);
        //printf("%f | %f\n",p_AC.x,p_AC.y);
        //printf("%f | %f\n",p_BC.x,p_BC.y);

	return p;
*/
}

CircleIntersection getIntersection(circle *A, circle *B){

	CircleIntersection returnobj;
	double a, dx, dy, d, h, rx, ry, x0, y0, x1, y1, r0, r1;
	double x2, y2;

	x0 = A->point.x;
	y0 = A->point.y;
	r0 = A->radius;

	x1 = B->point.x;
	y1 = B->point.y;
	r1 = B->radius;

	// dx and dy are the vertical and horizontal distances between
	// the circle centers.
	dx = x1 - x0;
	dy = y1 - y0;

	// Determine the straight-line distance between the centers.
	d = sqrt((dy * dy) + (dx * dx));

	// Check for solvability.
	if (d > (r0 + r1)) {
		// no solution. circles do not intersect.

		returnobj.success = false;
		//printf("Die Kreise haben keinen Schnittpunkt\n");
		return returnobj;
	}
	if (d < fabs(r0 - r1)) {
		// no solution. one circle is contained in the other
		returnobj.success = false;
		//printf("Ein Kreis ist in dem anderen Enthalten -> kein schnittpunkt\n");
		return returnobj;
	}

	// 'point 2' is the point where the line through the circle
	// intersection points crosses the line between the circle
	// centers.


	// Determine the distance from point 0 to point 2.
	a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;

	// Determine the coordinates of point 2.
	x2 = x0 + (dx * a/d);
	y2 = y0 + (dy * a/d);

	// Determine the distance from point 2 to either of the
	// intersection points.
	h = sqrt((r0*r0) - (a*a));

	// Now determine the offsets of the intersection points from
	// point 2.
	rx = -dy * (h/d);
	ry = dx * (h/d);

	// Determine the absolute intersection points.
	double xi 	= x2 + rx;
	double xi_prime = x2 - rx;
	double yi 	= y2 + ry;
	double yi_prime = y2 - ry;


	returnobj.a.x = xi;
	returnobj.a.y = yi;
	returnobj.b.x = xi_prime;
	returnobj.b.y = yi_prime;
	returnobj.success = true;
	return returnobj;
}








point point_AB(circle *A, circle *B, circle *C){

        A->tmp_P = (pow(A->radius,2)) - (pow(B->radius,2)) - (pow(A->point.x,2)) + (pow(B->point.x,2)) - (pow(A->point.y,2)) + (pow(B->point.y,2));
        A->tmp_s = (-1) * (B->point.x - A->point.x) / (B->point.y - A->point.y);
        A->tmp_q = (A->tmp_P - 2*(A->point.y)*(B->point.y - A->point.y)) / (2*(B->point.y - A->point.y));

        //printf("A->P = %f\n",A->tmp_P);
        //printf("A->s = %f\n",A->tmp_s);
        //printf("A->q = %f\n",A->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*A->tmp_s*A->tmp_q) - (2*A->point.x)) / (1+ (pow(A->tmp_s,2)));
        q = ((pow(A->tmp_q,2)) + (pow(A->point.x,2)) - (pow(A->radius,2))) / (1 + (pow(A->tmp_s,2)));

        //printf("p = %f\n",p);
        //printf("q = %f\n",q);

        point p_AB = pq_equation(p,q);

        point x0,x1;
        x0.x = p_AB.x;
        x1.x = p_AB.y;

        //Y-Wert ausrechnen
        x0.y = (A->tmp_P - 2*x0.x*(B->point.x - A->point.x)) / (2* (B->point.y - A->point.y));
        x1.y = (A->tmp_P - 2*x1.x*(B->point.x - A->point.x)) / (2* (B->point.y - A->point.y));

        //printf("p_AB: Die nullstellen sind\n");
        //printf("( %f | %f )\n",x0.x,x0.y);
        //printf("( %f | %f )\n",x1.x,x1.y);

        p_AB = determine_point_radius(C,x0,x1);
        //printf("p_AB: ( %f | %f )\n",p_AB.x,p_AB.y);
	return p_AB;
}

point point_AC(circle *A, circle *B, circle *C){

        A->tmp_P = (pow(A->radius,2)) - (pow(C->radius,2)) - (pow(A->point.x,2)) + (pow(C->point.x,2)) - (pow(A->point.y,2)) + (pow(C->point.y,2));
        A->tmp_s = (-1) * (C->point.x - A->point.x) / (C->point.y - A->point.y);
        A->tmp_q = (A->tmp_P - 2*(A->point.y)*(C->point.y - A->point.y)) / (2*(C->point.y - A->point.y));

        //printf("A->P = %f\n",A->tmp_P);
        //printf("A->s = %f\n",A->tmp_s);
        //printf("A->q = %f\n",A->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*A->tmp_s*A->tmp_q) - (2*A->point.x)) / (1+ (pow(A->tmp_s,2)));
        q = ((pow(A->tmp_q,2)) + (pow(A->point.x,2)) - (pow(A->radius,2))) / (1 + (pow(A->tmp_s,2)));

        //printf("p = %f\n",p);
        //printf("q = %f\n",q);

        point p_AC = pq_equation(p,q);

        point x0,x1;
        x0.x = p_AC.x;
        x1.x = p_AC.y;

        //Y-Wert ausrechnen
        x0.y = (A->tmp_P - 2*x0.x*(C->point.x - A->point.x)) / (2* (C->point.y - A->point.y));
        x1.y = (A->tmp_P - 2*x1.x*(C->point.x - A->point.x)) / (2* (C->point.y - A->point.y));

        //printf("p_AC: Die nullstellen sind\n");
        //printf("( %f | %f )\n",x0.x,x0.y);
        //printf("( %f | %f )\n",x1.x,x1.y);

        p_AC = determine_point_radius(B,x0,x1);
        //printf("p_AC: ( %f | %f )\n",p_AC.x,p_AC.y);
        return p_AC;
}

point point_BC(circle *A, circle *B, circle *C){

        B->tmp_P = (pow(B->radius,2)) - (pow(C->radius,2)) - (pow(B->point.x,2)) + (pow(C->point.x,2)) - (pow(B->point.y,2)) + (pow(C->point.y,2));
        B->tmp_s = (-1) * (C->point.x - B->point.x) / (C->point.y - B->point.y);
        B->tmp_q = (B->tmp_P - 2*(B->point.y)*(C->point.y - B->point.y)) / (2*(C->point.y - B->point.y));

        //printf("B->P = %f\n",B->tmp_P);
        //printf("B->s = %f\n",B->tmp_s);
        //printf("B->q = %f\n",B->tmp_q);

        //Gleichung für die pq-Formel
        //x^2 + p*x + q = 0
        double p,q;

        p = ((2*B->tmp_s*B->tmp_q) - (2*B->point.x)) / (1+ (pow(B->tmp_s,2)));
        q = ((pow(B->tmp_q,2)) + (pow(B->point.x,2)) - (pow(B->radius,2))) / (1 + (pow(B->tmp_s,2)));

        //printf("p = %f\n",p);
        //printf("q = %f\n",q);

        point p_BC = pq_equation(p,q);

        point x0,x1;
        x0.x = p_BC.x;
        x1.x = p_BC.y;

        //Y-Wert ausrechnen
        x0.y = (B->tmp_P - 2*x0.x*(C->point.x - B->point.x)) / (2* (C->point.y - B->point.y));
        x1.y = (B->tmp_P - 2*x1.x*(C->point.x - B->point.x)) / (2* (C->point.y - B->point.y));

        //printf("p_BC: Die nullstellen sind\n");
        //printf("( %f | %f )\n",x0.x,x0.y);
        //printf("( %f | %f )\n",x1.x,x1.y);

        p_BC = determine_point_radius(A,x0,x1);
        //printf("p_BC: ( %f | %f )\n",p_BC.x,p_BC.y);
        return p_BC;
}

point determine_point_radius(circle* circle, point x0, point x1){

	//Den Punkt bestimmen der in dem Kreis liegt
	double d1,d2;
        d1 = sqrt( pow((circle->point.x - x0.x),2) + pow((circle->point.y - x0.y),2) );//Abstand von Kreismittelpunkt zu x0
	//printf("Punkt %f %f abstand d1: %f\n",x0.x,x0.y,d1);

	//printf("Vergleich: %f == %f\n",d1,circle->radius);
        if( (d1 < circle->radius) || (COMPARE(d1,circle->radius))){
                //printf("Punkt (%f|%f) liegt in dem Kreis\n",x0.x,x0.y);
		return x0;
        }else{
                d2 = sqrt( pow((circle->point.x - x1.x),2) + pow((circle->point.y - x1.y),2) );//Abstand von Kreismittelpunkt zu x1
		//printf("Punkt %f %f abstandd d2: %f\n",x1.x,x1.y,d2);
        
       		if((d2 < circle->radius) || (COMPARE(d2,circle->radius))){
			//printf("Punkt (%f|%f) liegt in dem Kreis C\n",x1.x,x1.y);
       			//printf("Punkt %f %f abstand: %f\n",x1.x,x1.y,d2);

			return x1;
		}else{
			if(COMPARE(d1,d2)){
				//printf("Beide Punkte liegen im Kreis -> Beide Punkte sind gleich\n");
				return x1;
			}else{
				//printf("ERROR: keine der beiden Punkte liegt in dem Kreis. -> Ist nicht möglich !!!\n");
			}
		}
        }
	x0.x = NAN;
	x0.y = NAN;
	return x0;
}

point pq_equation(double p, double q){

	point erg;
	//Diskriminante
	double D = ((p*p)/4) - q;
	//printf("Diskriminante = %f\n",D);

	if(D > 0){
		//2 lösungen
		//printf("Es gibt 2 Lösungen\n");
		erg.x = -p/2 + sqrt(((p*p)/4) - q); 
		erg.y = -p/2 - sqrt(((p*p)/4) - q);
		
		//printf("x1 = %f\n",erg.x);
		//printf("x2 = %f\n",erg.y);

	}else if(D == 0){
		//eine lösung
		//printf("Es gibt 1 Lösung\n");
		erg.x = -p/2 + sqrt(((p*p)/4) - q);
		//printf("x1 = %f\n",erg.x);

	}else{
		//komplexe Lösung
		//printf("Es gibt keine Lösung\n");
		erg.x = NAN;
		erg.y = NAN;
	}
	return erg;
}
