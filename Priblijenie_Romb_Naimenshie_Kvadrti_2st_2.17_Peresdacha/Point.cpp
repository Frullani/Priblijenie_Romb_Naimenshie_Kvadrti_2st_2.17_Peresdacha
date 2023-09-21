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

//Запись точек в файл
void writePointsToFile(vector<Point> Points, const string& filename){
    ofstream file(filename);
    for(int i=0; i<Points.size(); i++){
        file << Points[i].x << " " << Points[i].y << " " << Points[i].z << " " << Points[i].color << endl;
    }
    cout << Points.size() << " Points writen to file" << endl;
}

//Раскрашивание сетки
vector<vector<Point>> colorizeNet(vector<vector<Point>> Net){
    unsigned long l, h;
    
    l=Net.size();
    h=Net[0].size();
    
    double step;
    
    Net[0][0].color=0;
    step=0.5/l;
    
    for(unsigned long i=1; i<=l-1; i++){
        for(int j=1; j<=i+1; j++){
            Net[i-(j-1)][j-1].color=i*step;
            //cout << "Net " << i-(j-1) << " "<<  j-1 << " color =" << Net[i-(j-1)][j-1].color << endl;
        }
    }
    
    step=0.5/l;
    
    unsigned long counter = 0;
    
    for(unsigned long i=1; i<=l-1; i++){
        
        for(unsigned long j=1; j<=l-i; j++){
            Net[i+(j-1)][l-1-(j-1)].color=i*step+0.5;
            //cout << "Net " << i+(j-1) << " "<<  l-1-(j-1) << " color =" << Net[i][l-1-(j-1)].color << endl;
        }
    }
    
    
    
    return Net;
}

vector<Point> colorazePlus(vector<Point> Points){
    double mid=0;
    double delta=5;
    double left, right;
    vector<Point> colorPoints, help2;
    
    for(int i=0; i<Points.size(); i++){
        mid+=Points[i].z;
    }
    
    mid=mid/Points.size();
    bool triger=true;
    int t=0;
    
    while (triger) {
        vector<Point> help;
        t++;
        left=mid-delta*t;
        right=mid+delta*t;
        
        for(int i=0; i<Points.size(); i++){
            
            if((Points[i].z>left)&&(Points[i].z<right)){
                help.push_back(Points[i]);
            }
            
            double h1 = help.size();
            double h2 = Points.size();
            if(h1/h2>0.96){
                triger=false;
                colorPoints=help;
                //ищем минимальный и максимальный элемент
                double min=0, max=0;
                for(int j=0; j<colorPoints.size(); j++){
                    if(min > colorPoints[j].z) min = colorPoints[j].z;
                    if(max < colorPoints[j].z) max = colorPoints[j].z;
                }
                for(int j=0; j<colorPoints.size(); j++){
                    colorPoints[j].color=(colorPoints[j].z-min)/(max-min);
                }
            }
            help2=help;
        }
        
        
    }
    return colorPoints;
}
