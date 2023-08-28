//
//  Point.cpp
//  Priblijenie_Romb_Naimenshie_Kvadrti_2st_2.17_Peresdacha
//
//  Created by Arsenii Klevakin on 26.08.2023.
//

#include "Point.hpp"

Point::Point(double a, double b){
    x=a; y=b; z=0;
}

Point::Point(double a, double b, double c){
    x=a; y=b; z=c;
};

void Point::computeZ(){
    z=fn(x, y);
}

double computeDistance(Point A, Point B){
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}

double fn(Point A){
    return fn(A.x, A.y);
}

