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
    int _width;
    int _height;
    std::vector<Point*> points;
    std::vector<Line*> lines;
    std::vector<Point*> sortedPoints;
    
    public:
    Plane(int w, int h);
    ~Plane();
    int getWidth();// Width of plane is pixels
    int getHeight(); // Height of plane in pixels
    void setWidth(int w); // Set width of plane, syncs with window if context menu is still open
    void setHeight(int h); // Set height of plane, syncs with window if context menu is still open
    int getPointCount(); // Returns size of point vector
    int getLineCount(); // Returns size of line vector
    Point* getPoint(int i); // Returns pointer to ith point
    Line* getLine(int i); // Returns pointer to ith line
    bool sortPoints(); //sorts all points in the vector, first in vector is bottom point, and remaining are sorted based on angle
    void addPoint(Point* p); //update bounds & render on gui
    void addLine(Line* l); // render line
    void gScan(); //gscan algorithm
    void gRecurse(std::stack<Point*>* s, int i); //recursive part of gscan algorithm
};

#endif
