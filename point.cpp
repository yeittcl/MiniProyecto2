#include "point.h"
#include <string>


//Constructor de la estructura
Point::Point(double _x, double _y, int _population)
    : x(_x), y(_y), population(_population) {}


//Operador para la comparacion en la estructura utilizada (set)
bool Point::operator<(const Point& other) const
{
    if (x != other.x) {
        return x < other.x;
    }
    return y < other.y;
}