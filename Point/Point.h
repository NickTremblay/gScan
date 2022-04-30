#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Point {
    private:

    public:
    // Angle with base point
    double angle;
    // Distance from base point
    double distance;
    Point(int x, int y, sf::Color c);
    int x;
    int y;
    sf::Color color;
    void changeColor(sf::Color c);
    
    friend class Plane;
};

#endif
