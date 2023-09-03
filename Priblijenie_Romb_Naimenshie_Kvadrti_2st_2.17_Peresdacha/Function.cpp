//
//  Function.cpp
//  Priblijenie_Romb_Naimenshie_Kvadrti_2st_2.17_Peresdacha
//
//  Created by Arsenii Klevakin on 26.08.2023.
//

#include "Function.hpp"
#include <math.h>

double fn(double x, double  y){
    //return x*x+y*y;
    //return sqrt(x*x+y*y)+3*cos(sqrt(x*x+y*y))+5;
    //return sin(x*y);
    //return 100-3/(sqrt(x*x+y*y))+sin(sqrt(x*x+y*y))+sqrt(200-(x*x+y*y)+10*sin(x)+10*sin(y))/1000;
    //return sin(x) * sin(y) * (10 - cos(x + y));
    //double r = sqrt(x * x + y * y);
        //if (r == 0) {
         //   return 0.0; // Избегаем деления на ноль
        //}
        //return 5*sin(r) / r;
    //double term1 = sin(sqrt(x * x + y * y)); double term2 = cos(sqrt(x * x + y * y)); return 10*term1 * term2;
    double term1 = x * x + y * y;
        double term2 = sqrt(term1);
        return 10*sin(term2) / term2;
};


