#include "Point.h";
#include <iostream>
#include <string>

Point::Point(unsigned int x, unsigned int y, std::string c) {
    this->x = x;
    this->y = y;
    this->color = c;
}

void Point::changeColor(std::string color) {
}

void Point::drawLine(Point* p, std::string color) {
    
}
