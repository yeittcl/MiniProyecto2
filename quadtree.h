#pragma once

#include "point.h"
#include "node.h"
#include <set>
#include <vector>

using namespace std;

class Quadtree 
{
    private:
        Node* root;

    public:
        Quadtree(double _width, double _height);
        ~Quadtree();
        void insert(const Point& point);
        int countRegion(double x, double y, double width, double height);
        int agreggateRegion(double x, double y, double width, double height);
        int totalPoints();
        int totalNodes();
        vector<Point> list();
    
    private:
        void insertPoint(Node* node, const Point& point);
        bool contains(Node* node, const Point& point);
        void subdivide(Node* node);
        void searchRegion(Node* node, double searchX, double searchY, double searchWidth, double searchHeight, int& count);
        void populationRegion(Node* node, double searchX, double searchY, double searchWidth, double searchHeight, int& sum);
        int countPoints(Node* node);
        int countNodes(Node* node);
        void getAllPoints(Node* node, vector<Point>& result);
};