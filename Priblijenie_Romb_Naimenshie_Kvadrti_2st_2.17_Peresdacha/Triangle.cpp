//
//  Triangle.cpp
//  Priblijenie_Romb_Naimenshie_Kvadrti_2st_2.17_Peresdacha
//
//  Created by Arsenii Klevakin on 26.08.2023.
//

#include "Triangle.hpp"

double Triangle::computeSquare(Point A, Point B, Point C){
    double a, b, c, p;
    a=computeDistance(A, B);
    b=computeDistance(C, B);
    c=computeDistance(A, C);
    p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

void Triangle::computeSquare(){
    Point A, B, C;
    A=v1; B=v2; C=v3;
    double a, b, c, p;
    a=computeDistance(A, B);
    b=computeDistance(C, B);
    c=computeDistance(A, C);
    p=(a+b+c)/2;
    square = sqrt(p*(p-a)*(p-b)*(p-c));
}

void Triangle::computeCenterofMass(){
    centerOfMass.x=(v1.x+v2.x+v3.x)/3;
    centerOfMass.y=(v1.y+v2.y+v3.y)/3;
}


Triangle::Triangle(){
    
}

Triangle::Triangle(Point a, Point b, Point c){
    v1=a; v2=b; v3=c;
    square=computeSquare(a, b, c);
}

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3){
    v1.x = x1; v1.y = y1;
    v2.x = x2; v2.y = y2;
    v3.x = x3; v3.y = y3;
    square=computeSquare(v1, v2, v3);
}

bool Triangle::isPointInside(Point A){
    double epsilon=0.000001;
    double a, b, c, S;
    a=computeSquare(A, v1, v2);
    b=computeSquare(A, v1, v3);
    c=computeSquare(A, v3, v2);
    S=a+b+c;
    if(abs(S-square)>epsilon) return false;
    else return true;
}


Point Triangle::computeFormula(int k, int l, vector<double> x, vector<double> y){
    Point A;
    A.x=(x[k]+x[l])/2;
    A.y=(y[k]+y[l])/2;
    return A;
}

void Triangle::computeP1_6(){
    Point zero(0, 0, 0);
    P.push_back(zero);
    
    P.push_back(v1); P.push_back(v2); P.push_back(v3);
    
    vector<double> x;
    vector<double> y;
    
    x.push_back(0); x.push_back(v1.x); x.push_back(v2.x); x.push_back(v3.x);
    y.push_back(0); y.push_back(v1.y); y.push_back(v2.y); y.push_back(v3.y);
    
    P.push_back(computeFormula(1, 2, x, y));
    P.push_back(computeFormula(2, 3, x, y));
    P.push_back(computeFormula(1, 3, x, y));
}

double Triangle::computeL(Point A, Point B, Point XY){
    double u1=A.x, v1=A.y;
    double u2=B.x, v2=B.y;
    double x=XY.x, y=XY.y;
    return (x-u1)*(v2-v1)-(y-v1)*(u2-u1);
}


double Triangle::computePsi(int i, Point XY){
    switch (i) {
        case 1:
            return computeL(P[2], P[3], XY);
            break;
        case 2:
            return computeL(P[1], P[3], XY);
            break;
        case 3:
            return computeL(P[1], P[2], XY);
            break;
        case 4:
            return computeL(P[4], P[6], XY);
            break;
        case 5:
            return computeL(P[4], P[5], XY);
            break;
        case 6:
            return computeL(P[5], P[6], XY);
            break;
        default:
            return 0;
            break;
    }
}

double Triangle::multiply2Psi(int a, int b, Point XY){
    return computePsi(a, XY)*computePsi(b, XY);
}

double Triangle::computeNu(int i, Point XY){
    switch (i) {
        case 1:
            return multiply2Psi(1, 4, XY);
            break;
        case 2:
            return multiply2Psi(2, 5, XY);
            break;
        case 3:
            return multiply2Psi(3, 6, XY);
            break;
        case 4:
            return multiply2Psi(1, 2, XY);
            break;
        case 5:
            return multiply2Psi(2, 3, XY);
            break;
        case 6:
            return multiply2Psi(1, 3, XY);
            break;
        default:
            return 0;
            break;
    }
}

double Triangle::computeFi(int i, Point XY){
    return computeNu(i, XY)/computeNu(i, P[i]);
}

double Triangle::Pf(Point XY){
    double res=0;
    for(int i=1; i<=10; i++){
        res=res+fn(P[i])*computeFi(i, XY);
    }
    return res;
}

vector<Point> generateRandomPointsInsideTriangle(Triangle triangle, int n) {
    vector<Point> randomPoints;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        double r1 = dis(gen);
        double r2 = dis(gen);

        if (r1 + r2 <= 1.0) {
            double x = triangle.v1.x + r1 * (triangle.v2.x - triangle.v1.x) +
                       r2 * (triangle.v3.x - triangle.v1.x);
            double y = triangle.v1.y + r1 * (triangle.v2.y - triangle.v1.y) +
                       r2 * (triangle.v3.y - triangle.v1.y);
            randomPoints.push_back({x, y});
        }
        else i--;
    }
    
    return randomPoints;
}

vector<Triangle> Make_Triangulation_Delane(Triangle MasterTriangle, vector<Point> points){
    vector<Triangle> triangles;
    //Найти треугольник которому принадлежит точка
    //Созать 4 новых треугольника по 4м точкам
    //Добавить 4 треугольника в масив
    triangles.push_back(MasterTriangle);
    for(int i=0; i<points.size(); i++){
        for(int j=0; j<triangles.size(); j++){
            if(triangles[j].isPointInside(points[i])){
                Triangle T=triangles[j];
                Triangle A(T.v1, T.v2, points[i]);
                Triangle B(T.v1, points[i], T.v3);
                Triangle C(points[i], T.v2, T.v3);
                triangles.erase(triangles.begin() + j);
                triangles.push_back(A);
                triangles.push_back(B);
                triangles.push_back(C);
                break;
            }
        }
    }
    
    return triangles;
}

double computeIntergralOnTriagle(Triangle T, int accuracy){
    vector<Point> Points = generateRandomPointsInsideTriangle(T, accuracy);
    vector<Triangle> Triangulation = Make_Triangulation_Delane(T, Points);
    for(int i=0; i<Triangulation.size(); i++){
        Triangulation[i].computeCenterofMass();
        Triangulation[i].centerOfMass.computeZ();
        Triangulation[i].computeSquare();
    }
    double Integral=0;
    
    for(int i=0; i<Triangulation.size(); i++){
        Integral += Triangulation[i].square*Triangulation[i].centerOfMass.z;
    }
    return Integral;
}

vector<Triangle> splitTriangle(Triangle T, int depth){
    vector<Triangle> Triangles;
    if(depth == 0){
        Triangles.push_back(T);
    }
    else{
        Point A, B, C;
        A.x=(T.v1.x+T.v2.x)/2; A.y=(T.v1.y+T.v2.y)/2;
        B.x=(T.v1.x+T.v3.x)/2; B.y=(T.v1.y+T.v3.y)/2;
        C.x=(T.v2.x+T.v3.x)/2; C.y=(T.v2.y+T.v3.y)/2;
        Triangle T1(T.v1, A, B);
        Triangle T2(T.v2, A, C);
        Triangle T3(T.v3, C, B);
        Triangle T4(C, A, B);
        
        vector<Triangle> subTriangles = splitTriangle(T1, depth-1);
        Triangles.insert(Triangles.end(), subTriangles.begin(), subTriangles.end());
        
        subTriangles = splitTriangle(T2, depth-1);
        Triangles.insert(Triangles.end(), subTriangles.begin(), subTriangles.end());
        
        subTriangles = splitTriangle(T3, depth-1);
        Triangles.insert(Triangles.end(), subTriangles.begin(), subTriangles.end());
        
        subTriangles = splitTriangle(T4, depth-1);
        Triangles.insert(Triangles.end(), subTriangles.begin(), subTriangles.end());
    }
    return Triangles;
}


double computeLeftIntegral(Triangle T, int i, int j, int deepth){
    vector<Triangle> Triangulation = splitTriangle(T, deepth);
    for(int t=0; t<Triangulation.size(); t++){
        Triangulation[t].computeCenterofMass();
        Point C=Triangulation[t].centerOfMass;
        Triangulation[t].centerOfMass.z=T.computeFi(i, C)*T.computeFi(j, C);
        
        Triangulation[t].computeSquare();
    }
    
    double Integral=0;
    
    for(int t=0; t<Triangulation.size(); t++){
        Integral += Triangulation[t].square*Triangulation[t].centerOfMass.z;
    }
    
    return Integral;
}

double computeRightIntegral(Triangle T, int i, int deepth){
    vector<Triangle> Triangulation = splitTriangle(T, deepth);
    for(int t=0; t<Triangulation.size(); t++){
        Triangulation[t].computeCenterofMass();
        Point C=Triangulation[t].centerOfMass;
        //cout << T.isPointInside(C) << endl;
        Triangulation[t].centerOfMass.z=fn(C)*T.computeFi(i, C);
        //cout << T.computeFi(i, C) << endl;
        Triangulation[t].computeSquare();
    }
    
    double Integral=0;
    
    for(int t=0; t<Triangulation.size(); t++){
        Integral += Triangulation[t].square*Triangulation[t].centerOfMass.z;
    }
    
    return Integral;

}

void Triangle::computeAlphas(int depth){
    vector<vector<double>> A(6, vector<double>(6, 0.0));
    for(int i=0; i<=5; i++){
        for(int j=0; j<=5; j++){
            A[i][j]=computeLeftIntegral(*this, i+1, j+1, depth);
        }
    }
    
    vector<double> B(6);
    for(int i=0; i<=5; i++){
        B[i]=computeRightIntegral(*this, i+1, depth);
    }
    
    alphas=solveEquations(A, B);
}

double Triangle::mnkPf(Point XY){
    double r=0;
    for(int i=0; i<=5; i++){
        r+=alphas[i]*computeFi(i+1, XY);
    }
    return r;
}


vector<Triangle> splitTo90Triangles(double x1, double y1, double x2, double y2, int n, Triangle M,  Triangle N){
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
    
    vector<Triangle> Triangles;
    for(int i=0; i<Net.size()-1; i++){
        for(int j=0; j<Net[i].size()-1; j++){
            Point A = Net[i][j];
            Point B = Net[i+1][j];
            Point C = Net[i][j+1];
            Point D = Net[i+1][j+1];
            Triangle T1(A,B,C);
            Triangle T2(B,C,D);
            T1.computeCenterofMass();
            T2.computeCenterofMass();
            Triangles.push_back(T1);
            Triangles.push_back(T2);
        }
    }
    
    vector<Triangle> Triangulation;
    
    for(int i=0; i<Triangles.size(); i++){
        if(M.isPointInside(Triangles[i].centerOfMass)){
            Triangulation.push_back(Triangles[i]);
        }
        if(N.isPointInside(Triangles[i].centerOfMass)){
            Triangulation.push_back(Triangles[i]);
        }
    }
    
    return Triangulation;
}
