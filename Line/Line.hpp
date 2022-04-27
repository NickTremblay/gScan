#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Line{
    public:
    // Set color of line
    void setColor(sf::Color c);
    // Static vertex array of SFML points to pass into window.draw()
    sf::Vertex vertices[2];
    // Construct line from 2 points and a SFML color
    Line(int x1, int y1, int x2, int y2, sf::Color c);
};

#endif
