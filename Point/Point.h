#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point {
    private:
    unsigned int x;
    unsigned int y;
    std::string color;
    
    public:
    Point(unsigned int x, unsigned int y, std::string c);
    void changeColor(std::string c);
    void drawLine(Point* p, std::string c);
    
    friend class Plane;
};

#endif
