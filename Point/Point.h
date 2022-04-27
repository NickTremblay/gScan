#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point {
    private:

    public:
    // Angle with base point
    double angle;
    // Distance from base point
    double distance;
    Point(int x, int y, std::string c);
    int x;
    int y;
    std::string color;
    void changeColor(std::string c);
    void drawLine(Point* p, std::string c);
    
    friend class Plane;
};

#endif
