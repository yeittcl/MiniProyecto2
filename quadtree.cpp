#include "quadtree.h"
#include "point.h"
#include "node.h"
#include <set>
#include <vector>

//METODOS PUBLICOS

//Constructor que inicializa la clase en el punto (0,0) y un ancho
//que sera la distancia en x (hacia los x-positivos) y un alto
//que sera la distancia en y (hacia las y-positivas), por lo que
//el punto (0,0) es el punto inferior izquierdo
Quadtree::Quadtree(double _width, double _height)
{
    root = new Node(0.0, 0.0, _width, _height);
}

//destructor de la clase
Quadtree::~Quadtree()
{
    delete root;
}

//insercion de puntos de tipo Punto, que se delega al metodo privado
//insertPoint - (Metodo mas abajo)
void Quadtree::insert(const Point& point)
{
    insertPoint(root, point);
}

//Metodo que cuenta los puntos en una region dada
//dado el punto inferior izquierdo (x,y)
//un ancho (hacia las x-positivas) y un alto (y-positivas)
//busca recursivamente los puntos que se encuentran en los nodos que
//caigan dentro de la region dada
//se delega la busqueda a un metodo privada (ver mas abajo) 
int Quadtree::countRegion(double x, double y, double width, double height)
{
    int count = 0;
    searchRegion(root, x, y, width, height, count);
    return count;
}

//Metodo que suma los puntos en una region dada
//dado el punto inferior izquierdo (x,y)
//un ancho (hacia las x-positivas) y un alto (y-positivas)
//busca recursivamente los puntos que se encuentran en los nodos que
//caigan dentro de la region dada y suma sus poblaciones
//se delega la busqueda a un metodo privada (ver mas abajo) 
int Quadtree::agreggateRegion(double x, double y, double width, double height)
{
    int sum = 0;
    populationRegion(root, x, y, width, height, sum);
    return sum;
}

//Cuenta todos los puntos existentes en el quadtree
//se delega la busqueda a un metodo privada (ver mas abajo) 
int Quadtree::totalPoints()
{
    return countPoints(root);
}

//cuenta todos los nodos creados (no nulos) en el quadtree
//se delega la busqueda a un metodo privada (ver mas abajo) 
int Quadtree::totalNodes()
{
    return countNodes(root);
}

//Metodo que retorna un contenedor, en este caso un vector, con todos los puntos existentes
//se delega la busqueda a un metodo privada (ver mas abajo) 
vector<Point> Quadtree::list()
{
    vector<Point> result;
    getAllPoints(root, result);
    return result;
}

//METODOS PRIVADOS


//Metodo de insercion:
//1-ero: se comparan los bordes del quadtree con el punto para ver si este lo puede contener (ver metodo contains)
//2-do: al utilizar un set como contenedor de los puntos, se verificar que solo exista un punto unico
// y ademas se analiza si ya se llego al punto maximo (4 puntos por nodo)
//3-ero: si se lleno el set, se crean 4 nodos(quadtree) (ver metodo de subdivision)
void Quadtree::insertPoint(Node* node, const Point& point)
{
    if(!contains(node, point))
    {
        return;
    }

    if(node->points.size() < 4)
    {
        node->points.insert(point);
    } else
    {
        if(node->children[0] == nullptr)
        {
            subdivide(node);
        }

        for(Node* child : node->children)
        {
            insertPoint(child, point);
        }
    }
}

//Compara los bordes del quadtree con el punto
bool Quadtree::contains(Node* node, const Point& point)
{
    return point.x >= node->x &&
           point.x < node->x + node->width &&
           point.y >= node->y &&
           point.y < node->y + node->height;
}

//Subdivide el quadtree, en cuatro quadtree con 1/4 de su tamaño
//El primer cuadrante es el cuadrante inferior izquierdo
//El segundo cuadrante es el cuadrante inferior derecho
//El tercer cuadrante es el cuadrante superior izquierdo
//El cuarto cuadrante es el cuadrante superior derecho
//cada subcuadrante tiene su origen en la punta inferior izquierda
void Quadtree::subdivide(Node* node)
{
    double subWidth = node->width / 2.0;
    double subHeight = node->height / 2.0;
    double x = node->x;
    double y = node->y;

    node->children[0] = new Node(x, y, subWidth, subHeight);  // Top-left
    node->children[1] = new Node(x + subWidth, y, subWidth, subHeight);  // Top-right
    node->children[2] = new Node(x, y + subHeight, subWidth, subHeight);  // Bottom-left
    node->children[3] = new Node(x + subWidth, y + subHeight, subWidth, subHeight);  // Bottom-right
}

//El metodo hace una busqueda recursiva mediante los bordes de la region, si un nodo se intersecta con la region, entonces
//podria tener puntos dentro de la interseccion, va aumentando un contador por cada punto que si se encuentra dentro,  se va haciendo
//la busqueda con los nodos hijos de este, hasta llegar a algun nodo null
void Quadtree::searchRegion(Node* node, double searchX, double searchY, double searchWidth, double searchHeight, int& count)
{
    if (node == nullptr) {
        return;
    }

    if (node->x >= searchX + searchWidth || node->x + node->width <= searchX ||
        node->y >= searchY + searchHeight || node->y + node->height <= searchY) {
        return;
    }

    for (const Point& point : node->points) {
        if (point.x >= searchX && point.x < searchX + searchWidth &&
            point.y >= searchY && point.y < searchY + searchHeight) {
            count++;
        }
    }

    for (Node* child : node->children) {
        searchRegion(child, searchX, searchY, searchWidth, searchHeight, count);
    }
}

//El metodo hace una busqueda recursiva mediante los bordes de la region, si un nodo se intersecta con la region, entonces
//podria tener puntos dentro de la interseccion, se van sumando las poblaciones de cada punto que si se encuentra dentro de la region,  se va haciendo
//la busqueda con los nodos hijos de este, hasta llegar a algun nodo null

void Quadtree::populationRegion(Node* node, double searchX, double searchY, double searchWidth, double searchHeight, int& sum)
{
    if (node == nullptr) {
        return;
    }

    if (node->x >= searchX + searchWidth || node->x + node->width <= searchX ||
        node->y >= searchY + searchHeight || node->y + node->height <= searchY) {
        return;
    }

    for (const Point& point : node->points) {
        if (point.x >= searchX && point.x < searchX + searchWidth &&
            point.y >= searchY && point.y < searchY + searchHeight) {
            sum += point.population;
        }
    }

    for (Node* child : node->children) {
        populationRegion(child, searchX, searchY, searchWidth, searchHeight, sum);
    }
}

//cuenta todos los puntos de todos los nodos recursivamente, hasta llegar a algun nodo null
int Quadtree::countPoints(Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    int count = node->points.size();

    for (Node* child : node->children) {
        count += countPoints(child);
    }

    return count;
}

//cuenta todos los nodos, y los hijos de este recursivamente
int Quadtree::countNodes(Node* node)
{
    if (node == nullptr) {
        return 0;
    }

    int count = 1; // Cuenta el nodo root

    for (Node* child : node->children) {
        count += countNodes(child);
    }

    return count;
}

//guarda todos los puntos de todos los nodos recursivamente hasta encontrar un nodo null
//estos se van guardando en un vector
void Quadtree::getAllPoints(Node* node, vector<Point>& result)
{
    if (node == nullptr) {
        return;
    }

    for (const Point& point : node->points) {
        result.push_back(point);
    }

    for (Node* child : node->children) {
        getAllPoints(child, result);
    }
}