#pragma once

#include "point.h"
#include <set>
#include <vector>

using namespace std;

struct Node
{
    double x;
    double y;
    double width;
    double height;
    set<Point> points;
    vector<Node*> children;

    Node(double _x, double _y, double _width, double _height);
    ~Node();
};
