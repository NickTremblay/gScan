#include "Point.h"
#include <iostream>
#include <string>

Point::Point(int x, int y, std::string c) {
    this->x = x;
    this->y = y;
    this->color = c;
}

void Point::changeColor(std::string c) {
    this->color = c;
}

void Point::drawLine(Point* p, std::string c) {
    
}
