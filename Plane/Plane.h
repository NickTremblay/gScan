#ifndef PLANE_H
#define PLANE_H

#include "../Point/Point.h"
#include "../Line/Line.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <algorithm>

class Plane {
    private:
    std::vector<Point*> sortedPoints;
    
    public:
    int width;
    int height;
    std::vector<Point*> points;
    std::vector<Line*> lines;
    Plane(int w, int h);
    ~Plane();
    bool sortPoints(); //sorts all points in the vector, first in vector is bottom point, and remaining are sorted based on angle
    void addPoint(Point* p); //update bounds & render on gui
    void addLine(Line* l); // render line
    void gScan(); //gscan algorithm
    void gRecurse(std::stack<Point*>* s, int i); //recursive part of gscan algorithm
};

#endif
