#include "quadtree.h"
#include "point.h"
#include "node.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono> 

using namespace std;

double convert_rounded(double number)
{
    number = (number * 1000);
    return number/1000;
}

void Prueba_insert(){
    vector<float> tiempos;


    srand(time(NULL));
    clock_t time_insert;
    clock_t time_insert2;

    time_insert = clock();

    for(int j=0; j<1; j++){
        Quadtree quadtree(360.000, 180.000);

        ifstream inputFile;
        inputFile.open("worldcitiespop_fixed.csv");
        string line = "";
        char delimitador = ';';
        int i = 0;

        getline(inputFile, line);

        time_insert = clock();

        while(getline(inputFile, line)){
            stringstream stream(line);
            string country, city, accentCity, region, strpopulation, strlatitude, strlongitude, geopoint, geolatitude, geolongitude;
            double latitude, longitude;
            int population;
            getline(stream, country, delimitador);
            getline(stream, city, delimitador);
            getline(stream, accentCity, delimitador);
            getline(stream, region, delimitador);
            getline(stream, strpopulation, delimitador);
            population = atoi(strpopulation.c_str());
            getline(stream, strlatitude, delimitador);
            getline(stream, strlongitude, delimitador);
            getline(stream, geopoint, delimitador);
            stringstream geostream(geopoint);
            getline(geostream, geolatitude, ',');
            getline(geostream, geolongitude, ',');
            latitude = convert_rounded(atof(geolatitude.c_str()));
            latitude+=90.000;
            longitude = convert_rounded(atof(geolongitude.c_str()));
            longitude+=180.000;
            quadtree.insert(Point(longitude, latitude, population));
            i++;
            if(i==100000 || i==200000 || i==400000 || i==800000 || i==1600000){
                time_insert2 = clock() - time_insert;
                tiempos.push_back(time_insert2);
            }
        }

        time_insert2 = clock() - time_insert;
        tiempos.push_back(time_insert2);

        while(!tiempos.empty()){
            std::cout<<tiempos.at(0)<<endl;
            tiempos.erase(tiempos.begin()+ 0);
        }
            std::cout<<quadtree.totalPoints()<<endl;
            std::cout<<quadtree.totalNodes()<<endl;
            
            inputFile.close();
    }
}

void Prueba_Region(){
    Quadtree quadtree(360.000, 180.000);

    ifstream inputFile;
    inputFile.open("worldcitiespop_fixed.csv");
    string line = "";
    char delimitador = ';';
    int i = 0;

    getline(inputFile, line);

    while(getline(inputFile, line)){
        stringstream stream(line);
        string country, city, accentCity, region, strpopulation, strlatitude, strlongitude, geopoint, geolatitude, geolongitude;
        double latitude, longitude;
        int population;
        getline(stream, country, delimitador);
        getline(stream, city, delimitador);
        getline(stream, accentCity, delimitador);
        getline(stream, region, delimitador);
        getline(stream, strpopulation, delimitador);
        population = atoi(strpopulation.c_str());
        getline(stream, strlatitude, delimitador);
        getline(stream, strlongitude, delimitador);
        getline(stream, geopoint, delimitador);
        stringstream geostream(geopoint);
        getline(geostream, geolatitude, ',');
        getline(geostream, geolongitude, ',');
        latitude = convert_rounded(atof(geolatitude.c_str()));
        latitude+=90.000;
        longitude = convert_rounded(atof(geolongitude.c_str()));
        longitude+=180.000;
        quadtree.insert(Point(longitude, latitude, population));
        i++;
    }
  
    srand(time(NULL));

    clock_t time_insert;

    std::cout<<"CountRegion"<<endl;
    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.countRegion(0,0,2,2);

        time_insert = clock() - time_insert;
        
        std::cout<<"[2x2]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.countRegion(0,0,50,42);

        time_insert = clock() - time_insert;
        
        std::cout<<"[50x42]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.countRegion(0,0,80,120);

        time_insert = clock() - time_insert;
        
        std::cout<<"[80x120]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.countRegion(0,0,200,180);

        time_insert = clock() - time_insert;
        
        std::cout<<"[200x180]: "<<time_insert<<endl;
    }

    std::cout<<endl;
    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.countRegion(0,0,360,180);

        time_insert = clock() - time_insert;
        
        std::cout<<"[360x180]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    std::cout<<"AggregateRegion"<<endl;
    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.agreggateRegion(0,0,2,2);

        time_insert = clock() - time_insert;
        
        std::cout<<"[2x2]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.agreggateRegion(0,0,50,42);

        time_insert = clock() - time_insert;
        
        std::cout<<"[50x42]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.agreggateRegion(0,0,80,120);

        time_insert = clock() - time_insert;
        
        std::cout<<"[80x120]: "<<time_insert<<endl;
    }
    std::cout<<endl;

    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.agreggateRegion(0,0,200,180);

        time_insert = clock() - time_insert;
        
        std::cout<<"[200x180]: "<<time_insert<<endl;
    }

    std::cout<<endl;
    for(int i=0; i<20; i++){
        time_insert = clock();

        int x1 = quadtree.agreggateRegion(0,0,360,180);

        time_insert = clock() - time_insert;
        
        std::cout<<"[360x180]: "<<time_insert<<endl;
    }
    std::cout<<endl;
    
                
    inputFile.close();
}


int main(){
    
    /*Prueba_insert(); */
    Prueba_Region();
    
    return 0;
}

// g++ main.cpp quadtree.cpp point.cpp node.cpp -o main.exe // 