#ifndef PLANE_H
#define PLANE_H

#include "../Point/Point.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>

class Plane {
    private:
    std::pair<unsigned int,unsigned int> xBounds;
    std::pair<unsigned int,unsigned int> yBounds;
    std::vector<Point*> points;
    unsigned int width;
    unsigned int height;
    
    public:
    Plane(char importMode);
    void sortPoints(); //sorts all points in the vector, first in vector is bottom point, and remaining are sorted based on angle
    void sortRecurse(int low, int high); //quick sort, gets called in sort points
    int sortPartition(int low, int high); //called in quick sort to find partition and sort around partition
    void addPoint(Point* p); //update bounds & render on gui
    void gScan(std::stack<Point*>* s); //gscan algorithm
    void gRecurse(std::stack<Point*>* s, int i); //recursive part of gscan algorithm
};

#endif
