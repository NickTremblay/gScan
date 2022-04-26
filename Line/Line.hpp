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
    Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, sf::Color c);
};

#endif
