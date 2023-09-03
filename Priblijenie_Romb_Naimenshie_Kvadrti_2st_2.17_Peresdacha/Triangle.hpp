//
//  Triangle.hpp
//  Priblijenie_Romb_Naimenshie_Kvadrti_2st_2.17_Peresdacha
//
//  Created by Arsenii Klevakin on 26.08.2023.
//

#ifndef Triangle_hpp
#define Triangle_hpp


#include <stdio.h>
#include "Point.hpp"
#include <vector>
#include <math.h>
#include <random>
#include "SolveByGaus.hpp"

using namespace std;

class Triangle{
public:
    //Вершины треугольника
    Point v1, v2, v3;
    
    //Точки из Сетки принаджлежащие данному треугольнику
    vector<Point> netPointsInside;
    
    double square;
    
    Point centerOfMass;
    
    //Список P_i
    vector<Point> P;
    
    vector<double> alphas;
    
    //Вычисление какой-то площади по трем точкам
    double computeSquare(Point A, Point B, Point C);
    //Вычисление и присваение площади данного треугольника
    void computeSquare();
    
    //Вычисление и присваение центра масс данного треугольнка
    void computeCenterofMass();
    
    Triangle();
    Triangle(Point a, Point b, Point c);
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
    
    //Проверка - Точка A внутри треугольника?
    bool isPointInside(Point A);
    
    //Служебная формула для вычисления Pi
    Point computeFormula(int k, int l, int s, vector<double> x, vector<double> y);
    
    //Вычисление и присваение данному треугольнику Pi
    void computeP1_10();
    
    //ДАЛЕЕ ИДУТ ФУНКЦИИ НУЖНЫЕ ДЛЯ МНОГОМЕРНОЙ ИНТРЕРПОЛЯЦИИ СТЕПЕНИ 2
    
    double computeL(Point A, Point B, Point XY);
    
    double computePsi(int i, Point XY);
    
    double multiply3Psi(int a, int b, int c, Point XY);
    
    double computeNu(int i, Point XY);
    
    double computeFi(int i, Point XY);
    
    //Интреполирующая функция
    double Pf(Point XY);
    
    void computeAlphas(int deepth);
    
    //Интреполирующая функция по методу наименьших квадратов
    double mnkPf(Point XY);
};

//Случайном образом генерирует n точек внутри треугольника
vector<Point> generateRandomPointsInsideTriangle(Triangle triangle, int n);

//Производит треангуляцию Делане внутри мастер треугольника по списку точек
vector<Triangle> Make_Triangulation_Delane(Triangle MasterTriangle, vector<Point> points);

//Вычисляет интергралл с нужной точностью внутри треугольника
double computeIntergralOnTriagle(Triangle T, int accuracy);

//Рекурсивно дробит треугольники на маленькие, делая разрезы по средим линиям
vector<Triangle> splitTriangle(Triangle T, int depth);

//Функции нужные для нахождения alphas 1-10 внтури системы
double computeLeftIntegral(Triangle T, int i, int j, int deepth);
double computeRightIntegral(Triangle T, int i, int deepth);

//Две функции вычисляющие правый и 

#endif /* Triangle_hpp */
