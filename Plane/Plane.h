#include "Point.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Plane {
    private:
    std::pair<unsigned int,unsigned int> xBounds;
    std::pair<unsigned int,unsigned int> yBounds;
    std::vector<Point*> points;
    unsigned int width;
    unsigned int height;
    
    public:
    Plane(char importMode);
    void sortPoints(); //sorts all points in the vector, first in vector is bottom point, and remaining are sorted based on angle
    void sortRecurse(int min); //quick sort, gets called in sort points
    void sortPartition(); //called in quick sort to find partition and sort around partition
    void addPoint(Point* p); //update bounds & render on gui
    void gScan(std::stack* s); //gscan algorithm
};