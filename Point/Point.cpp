#include "Point.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

Point::Point(int x, int y, sf::Color c) {
    this->x = x;
    this->y = y;
    this->color = c;
}

void Point::changeColor(sf::Color c) {
    this->color = c;
}
