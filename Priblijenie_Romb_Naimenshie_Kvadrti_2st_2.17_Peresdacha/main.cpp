/*
 Приближение функции, заданной в ромбе, конечными элементами степени 2
 методом наименьших квадратов.
 
 Алгоритм
 1.Ромб задается четырьмя парами координат x y, программа проверяет, что это действительно ромб
 2.Ромб делиться на две треугольника, и каждый из этих треугольников делиться на много мелких рекурсивным алгоритмом, с параметром depth
 3.Создается сетка для отрисовки интерполяции, покарывающая треугольник
 4.Отбираются точки сетки для каждого треугольника, которым они принадлежат
 5.Рассчитываются P_i, для каждого треугольника
 6.Рассчитываются alpha_i для каждого треугольника
 7.Вычисляются значения в точках принадлежащих треугольнику через Pf
 8.Запись этих точек в файл
 */

#include <iostream>
#include <fstream>
#include "Function.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include "SolveByGaus.hpp"

using namespace std;

//Проверяет по 4 точкам, Ромб ли это
bool isThisRombus(Point r1, Point r2, Point r3, Point r4){
    //Вычислим скалярное произведение диагоналей
    Point vect1, vect2;
    vect1.x=r3.x-r1.x; vect1.y=r3.y-r1.y;
    vect2.x=r4.x-r2.x; vect2.y=r4.y-r2.y;
    double res;
    res=vect1.x*vect2.x+vect1.y*vect2.y;
    if(res==0) return true;
    else return false;
}

//Создает сетку, с парамером плотности n
vector<Point> MakeNet(double x1, double y1, double x2, double y2, int n){
    vector<Point> Net;
    double hx, hy;
    hx=(x2-x1)/n; //шаг по x
    hy=(y1-y2)/n; //шаг по y
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            Point P;
            P.x=x1+j*hx;
            P.y=y2+i*hy;
            Net.push_back(P);
        }
    }
    return Net;
}

vector<vector<Point>> MakeNet2(double x1, double y1, double x2, double y2, int n){
    vector<vector<Point>> Net;
    double hx, hy;
    hx=(x2-x1)/n; //шаг по x
    hy=(y1-y2)/n; //шаг по y
    for(int i=0; i<=n; i++){
        vector<Point> help;
        for(int j=0; j<=n; j++){
            Point P;
            P.x=x1+j*hx;
            P.y=y2+i*hy;
            help.push_back(P);
        }
        Net.push_back(help);
    }
    return Net;
}

double findMin(double a, double b, double c, double d) {
    // Находим минимум между a и b
    double minAB = (a < b) ? a : b;
    // Находим минимум между c и d
    double minCD = (c < d) ? c : d;
    // Находим минимум между minAB и minCD
    double overallMin = (minAB < minCD) ? minAB : minCD;
    return overallMin;
}

double findMax(double a, double b, double c, double d) {
    // Находим минимум между a и b
    int maxAB = (a > b) ? a : b;
    // Находим минимум между c и d
    int maxCD = (c > d) ? c : d;
    // Находим минимум между minAB и minCD
    int overallMax = (maxAB > maxCD) ? maxAB : maxCD;
    return overallMax;
}


int main() {
    Point r1(0, -7), r2(-10, 0), r3(0, 7), r4(10, 0);
    int TriangulationSize=3; //2 это 256 треугольников Рекомендуется
    int NetSize=200;
    int IntegralAcuracy=3;
    
    if(isThisRombus(r1, r2, r3, r4)){
        cout << "Okay the input is Rombus" << endl;
    }
    else{
        cout << "Error the input is not Rombus" << endl;
        return 1;
    }
    
    //Разделяем ромб на две части и создаем трианглуляцию
    vector<Triangle> Triangulation;
    vector<Triangle> helpTriangles;
    Triangle RombPart1(r1, r2, r3), RombPart2(r3, r4, r1);
    
    Triangulation=splitTriangle(RombPart1, TriangulationSize);
    helpTriangles=splitTriangle(RombPart2, TriangulationSize);
    
    Triangulation.insert(Triangulation.end(), helpTriangles.begin(), helpTriangles.end());
    
    //Создаем сетку покрывающую ромб
    Point RectangleLeftTop(findMin(r1.x, r2.x, r3.x, r4.x), findMax(r1.y, r2.y, r3.y, r4.y));
    Point RectangleRightBottomn(findMax(r1.x, r2.x, r3.x, r4.x), findMin(r1.y, r2.y, r3.y, r4.y));
    //vector<Point> Net = MakeNet(RectangleLeftTop.x, RectangleLeftTop.y, RectangleRightBottomn.x, RectangleRightBottomn.y, NetSize);
    
    vector<Point> Net;
    vector<vector<Point>> Net2;
    Net2 = MakeNet2(RectangleLeftTop.x, RectangleLeftTop.y, RectangleRightBottomn.x,
                   RectangleRightBottomn.y, NetSize);
    Net2 = colorizeNet(Net2);
    for(int i=0; i<Net2.size(); i++){
        for(int j=0; j<Net2[i].size(); j++){
            Point P=Net2[i][j];
            Net.push_back(P);
        }
    }
    
    
    
    
    
    
    //Находим для каждой точки треугольник, которому принадлежит точка
    for(int i=0; i<Net.size(); i++){
        for(int j=0; j<Triangulation.size(); j++){
            if(Triangulation[j].isPointInside(Net[i])){
                Triangulation[j].netPointsInside.push_back(Net[i]);
                break;
            }
        }
    }
    
    //вычисляем ПЛОЩАДЬ, Z для всех вершин треугольника и Pi
    for(int i=0; i<Triangulation.size(); i++){
        Triangulation[i].computeSquare();
        Triangulation[i].v1.z=fn(Triangulation[i].v1);
        Triangulation[i].v2.z=fn(Triangulation[i].v2);
        Triangulation[i].v3.z=fn(Triangulation[i].v3);
        Triangulation[i].computeP1_10();
    }
    
    for(int i=0; i<Triangulation.size(); i++){
        Triangulation[i].computeAlphas(IntegralAcuracy);
    }
    
    cout << "Treagulation containing " << Triangulation.size() << " triangles is ready" << endl;
    
    //Вычисляем интерпалиционные значения через Pf
    vector<Point> AproxPoints;
    for(int i=0; i<Triangulation.size(); i++){
        for(int j=0; j<Triangulation[i].netPointsInside.size(); j++){
            Point XY = Triangulation[i].netPointsInside[j];
            XY.z=0;
            for(int k=1; k<=10; k++){
                //XY.z+=Triangulation[i].computeFi(k, XY)*alphas[k];
            }
            XY.z=Triangulation[i].mnkPf(XY);
            AproxPoints.push_back(XY);
        }
    }
    AproxPoints = colorazePlus(AproxPoints);
    //Вычисляем реальные значения
    vector<Point> RealPoints;
    
    for(int i=0; i<AproxPoints.size(); i++){
        Point A;
        A=AproxPoints[i];
        A.z=fn(A);
        RealPoints.push_back(A);
    }
    
    
    writePointsToFile(AproxPoints, "aprox_points.txt");
    writePointsToFile(RealPoints, "real_points.txt");
    
    double maxz=AproxPoints[0].z, minz=AproxPoints[0].z;
    for(int i=0; i<AproxPoints.size(); i++){
        if(AproxPoints[i].z>maxz) maxz=AproxPoints[i].z;
        if(AproxPoints[i].z<maxz) minz=AproxPoints[i].z;
    }
    cout << "maxz=" << maxz <<" minz=" << minz << endl;
   
    
    return 0;
}
