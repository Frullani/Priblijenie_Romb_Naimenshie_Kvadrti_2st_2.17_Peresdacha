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
#include <fstream>
#include <vector>
#include <iostream>
#include "SolveByGaus.hpp"

using namespace std;

class Point{
public:
    double x, y;
    double z;
    double color;
    
    Point(){};
    
    Point(double a, double b);
    Point(double a, double b, double c);
    
    void computeZ();
};

double computeDistance(Point A, Point B);
double fn(Point A);

//Запись точек в файл
void writePointsToFile(vector<Point> Points, const string& filename);

//Раскрашивание сетки
vector<vector<Point>> colorizeNet(vector<vector<Point>> Net);
vector<Point> colorazePlus(vector<Point> Points);
#endif /* Point_hpp */
