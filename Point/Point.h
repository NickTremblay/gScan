#include <iostream>
#include <string>

class Point {
    private:
    unsigned int x;
    unsigned int y;
    
    public:
    point(unsigned int x, unsigned int y);
    void changeColor(std::string color);
    void drawLine(Point* p, std::string color);
    
    friend class Plane;
};