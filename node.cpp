#include "node.h"
#include <set>
#include <vector>

using namespace std;

//constructor de la estructura
Node::Node(double _x, double _y, double _width, double _height)
    : x(_x), y(_y), width(_width), height(_height)
    {
        children.resize(4, nullptr);
    }

//destructor de la estructura
Node::~Node()
{
    for(Node* child : children)
    {
        delete child;
    }
}