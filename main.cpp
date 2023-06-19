#include "quadtree.h"
#include "point.h"
#include "node.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
    Quadtree quadtree(100.0, 100.0);

    quadtree.insert(Point(10.0, 10.0, 1000));
    quadtree.insert(Point(10.0, 10.0, 1000));
    quadtree.insert(Point(20.0, 20.0, 2000));
    quadtree.insert(Point(30.0, 30.0, 3000));
    quadtree.insert(Point(40.0, 40.0, 4000));
    quadtree.insert(Point(50.0, 50.0, 5000));
    quadtree.insert(Point(60.0, 60.0, 6000));
    quadtree.insert(Point(70.0, 70.0, 7000));
    quadtree.insert(Point(80.0, 80.0, 8000));
    quadtree.insert(Point(90.0, 90.0, 9000));
    quadtree.insert(Point(15.0, 25.0, 1500));
    quadtree.insert(Point(35.0, 45.0, 3500));
    quadtree.insert(Point(55.0, 65.0, 5500));
    quadtree.insert(Point(75.0, 85.0, 7500));
    quadtree.insert(Point(95.0, 95.0, 9500));
    quadtree.insert(Point(22.0, 32.0, 2200));
    quadtree.insert(Point(42.0, 52.0, 4200));

    float searchX = 20.0;
    float searchY = 20.0;
    float searchWidth = 40.0;
    float searchHeight = 40.0;

    int regioncount = quadtree.countRegion(searchX, searchY, searchWidth, searchHeight);
    cout<< "puntos en region: "<<regioncount<<endl;
    int regionpop = quadtree.agreggateRegion(searchX, searchY, searchWidth, searchHeight);
    cout<< "population en region: "<<regionpop<<endl;
    cout<< "total points: "<<quadtree.totalPoints()<<endl;
    cout<< "total node: "<<quadtree.totalNodes()<<endl;
    vector<Point> allpoints = quadtree.list();
    for(const Point& point: allpoints)
    {
        cout<<"point: "<<point.x<<", "<<point.y<<endl;
    }
    
    return 0;
}