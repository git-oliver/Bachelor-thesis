#include "../include.h"
#include <stdio.h>
#include <stdlib.h>


double calc_average(double data[], int len){

        double result = 0;

        for(int i=0; i<len; i++){
                result +=data[i];
        }
        return result / len;
}



