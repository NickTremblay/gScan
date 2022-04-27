#include "Line.hpp"
#include <SFML/Graphics.hpp>


Line::Line(int x1, int y1, int x2, int y2, sf::Color c){
    this->vertices[0].position = sf::Vector2f(x1, y1);
    this->vertices[0].color = c;
    this->vertices[1].position = sf::Vector2f(x2, y2);
    this->vertices[1].color = c;
}

void Line::setColor(sf::Color c){
    this->vertices[0].color = c;
    this->vertices[1].color = c;
}
