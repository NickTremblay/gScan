#include "Plane.h"
#include "../Line/Line.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <utility>
#include <vector>

Plane::Plane(unsigned int w, unsigned int h) {
    this->width = w;
    this->height = h;
}

bool Plane::sortPoints() {
    //finds the bottom-most point
    Point* min = this->points[0];
    int min_idx = 0;
    for(int i=0; i<points.size(); i++) {
        if((height - (points[i]->y) < (height - (min->y)))){
            min = points[i];
            min_idx = i;
        // If y is same as bottom-most point then choose left-most
        }else if((points[i]->y == min->y) && (points[i]->x < min->x)){
            min = points[i];
            min_idx = i;
        }
    }

    //switches the bottom left point to first in the vector
    Point* temp = this->points[0];
    this->points[0] = this->points[min_idx];
    this->points[min_idx] = temp;
    
    //calls a quicksort function to sort the vector relative to the min
    this->sortRecurse(1,this->points.size() - 1);

    // build sortedPoints
    points[0]->angle = -2;
    points[0]->distance = 0;
    sortedPoints.push_back(points[0]);
    for(int j = 1; j < points.size(); j++){
        Point* current = points[j];
        Point* prev = points[j - 1];
        
        // If angle is same as previous then keep whichever has greater distance
        if(current->angle == prev->angle){
            if(current->distance > prev->distance){
                sortedPoints.pop_back();
            }else continue;
        }
        
        sortedPoints.push_back(current);
        
    }
    
    //std::cout << "Sorted points" << std::endl;
    for(int k = 0; k < sortedPoints.size(); k++){
        //std::cout << sortedPoints[k]->x << "," << sortedPoints[k]->y << std::endl;
    }
    
    return (sortedPoints.size() >= 3);
}

void Plane::sortRecurse(int low, int high) {
    //quick sort, orders all points based on their angle from the min point
    if(low < high) {
        int part_idx = sortPartition(low,high);
        
        this->sortRecurse(low,part_idx-1);
        this->sortRecurse(part_idx+1,high);
    }
}

int Plane::sortPartition(int low, int high) {
    Point* pivot = this->points[high];
    int i = low - 1;
    int j_ang, p_ang;
    
    for(int j=low; j<high; j++) {
        //calculations to see whether j or pivot has the higher angle
        Point* j_point = this->points[j];
        Point* base = this->points[0];
        double j_ang = double(((height - j_point->y) - (height - base->y)));
        j_ang /= (j_point->x - base->x);
        double p_ang = double(((height - pivot->y) - (height - base->y)));
        p_ang /= (pivot->x - base->x);
        //flips all the negative slopes so that angles are counted in the right order
        //std::cout << "Point j(" << j_point->x << "," << j_point->y << ") and Point base(" << base->x << "," << base->y << ") have angle of " << j_ang << std::endl;
        //std::cout << "Point pivot(" << pivot->x << "," << pivot->y << ") and Point base(" << base->x << "," << base->y << ") have angle of " << p_ang << std::endl;
        if(j_ang < 0) {
            j_ang = 1 / j_ang;
        }
        if(p_ang < 0) {
            p_ang = 1 / p_ang;
        }

        
        // Save angle and distance of j_point for duplicate removal
        j_point->angle = j_ang;
        int xDis = std::pow(j_point->x - base->x, 2);
        int yDis = std::pow(j_point->y - base->y, 2);
        j_point->distance = sqrt(double(xDis + yDis));
        
        
        //actual quicksort swapping
        if(j_ang < p_ang) {
            i++;
            //swap i and j
            Point* temp = this->points[i];
            this->points[i] = this->points[j];
            this->points[j] = temp;
        }
    }
    
    i++;
    //swap high and i
    Point* temp = this->points[i];
    this->points[i] = this->points[high];
    this->points[high] = temp;
    return i;
}

void Plane::addPoint(Point* p) {
    points.push_back(p);
    
    if(p->x >= width - 20){
        height += 20;
    }
    
    if(p->y >= height - 20){
        height += 20;
    }
}

void Plane::addLine(Line* l){
    lines.push_back(l);
}

void Plane::gScan() {
    std::stack<Point*>* s = new std::stack<Point*>;
    //draws red line from start point to first point, pushes first 2 points to stack, sets counter i to 2
    int i = 2;
    addLine(new Line(this->sortedPoints[0]->x, this->sortedPoints[0]->y, this->sortedPoints[1]->x, this->sortedPoints[1]->y, sf::Color(255, 0, 0, 255)));
    
    s->push(this->sortedPoints[0]);
    s->push(this->sortedPoints[1]);
    
    this->gRecurse(s,i);
}

void Plane::gRecurse(std::stack<Point*>* s, int i) {
    //initial condition: i is the last in the point vector
    if(i == (this->sortedPoints).size()-1) {
        addLine(new Line(sortedPoints[0]->x, sortedPoints[0]->y, sortedPoints[i]->x, sortedPoints[i]->y, sf::Color::Red));
        return;
    }
    
    //draw blue line, push next point to stack
    addLine(new Line(s->top()->x, s->top()->y, this->sortedPoints[i]->x, this->sortedPoints[i]->y, sf::Color::Blue));
    s->push(this->sortedPoints[i]);
    
    //check direction of turn using top 3 points of stack
    Point* p3 = s->top();
    s->pop();
    Point* p2 = s->top();
    s->pop();
    Point* p1 = s->top();
    
    double slope1 = ((height - p2->y) - (height - p1->y)) / (p2->x - p1->x);
    double slope2 = ((height - p3->y) - (height - p2->y)) / (p3->x - p2->x);
    slope1 = 1/slope1;
    slope2 = 1/slope2;
    
    s->push(p2);
    s->push(p3);
    
    
    //if left turn, call again with i+1
    if(slope2 > slope1) {
        addLine(new Line(p2->x, p2->y, p3->x, p3->y, sf::Color::Red));
        this->gRecurse(s,i+1);
    }
    
    //if right turn, pop 2 off stack, remove their lines, keep i the same
    else {
        addLine(new Line(p1->x, p1->y, p2->x, p2->y, sf::Color::White));
        addLine(new Line(p2->x, p2->y, p3->x, p3->y, sf::Color::White));
        s->pop();
        s->pop();
        this->gRecurse(s,i);
    }
}
