#pragma once

#include <string>

using namespace std;

struct Point
{
    double x;
    double y;
    int population;

    Point(double _x, double _y, int _population);
    bool operator<(const Point& other) const;
};
