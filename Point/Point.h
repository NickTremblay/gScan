#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point {
    private:
    // Angle with base point
    double angle;
    
    // Distance from base point
    double distance;
    
    public:
    Point(unsigned int x, unsigned int y, std::string c);
    unsigned int x;
    unsigned int y;
    std::string color;
    void changeColor(std::string c);
    void drawLine(Point* p, std::string c);
    
    friend class Plane;
};

#endif
