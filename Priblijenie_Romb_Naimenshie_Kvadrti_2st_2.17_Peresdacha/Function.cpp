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
    return sqrt(x*x+y*y)+3*cos(sqrt(x*x+y*y))+5;
    //return sin(x*y);
}

