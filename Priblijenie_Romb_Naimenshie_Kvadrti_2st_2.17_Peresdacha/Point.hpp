//
//  Point.hpp
//  Priblijenie_Romb_Naimenshie_Kvadrti_2st_2.17_Peresdacha
//
//  Created by Arsenii Klevakin on 26.08.2023.
//

#ifndef Point_hpp
#define Point_hpp

#include "Function.hpp"
#include <stdio.h>
#include <math.h>

class Point{
public:
    double x, y;
    double z;
    
    Point(){};
    
    Point(double a, double b);
    Point(double a, double b, double c);
    
    void computeZ();
};

double computeDistance(Point A, Point B);
double fn(Point A);

#endif /* Point_hpp */
