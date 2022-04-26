#include "Plane.h"
#include "../Line/Line.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

Plane::Plane(unsigned int w, unsigned int h) {
    this->width = w;
    this->height = h;
}

void Plane::sortPoints() {
    //finds the bottom left point
    Point* min = this->points[0];
    int min_idx = 0;
    for(int i=0; i<points.size(); i++) {
        if(points[i]->y > min->y) {
            if(points[i]->x <= min->x) {
                min = points[i];
                min_idx = i;
            }
        }
    }

    //switches the bottom left point to first in the vector
    Point* temp = this->points[0];
    this->points[0] = this->points[min_idx];
    this->points[min_idx] = temp;
    
    //calls a quicksort function to sort the vector relative to the min
    this->sortRecurse(1,this->points.size() - 1);
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
        double j_ang = (j_point->y - base->y) / (j_point->x - base->x);
        double p_ang = (pivot->y - base->y) / (pivot->x - base->x);
        //flips all the negative slopes so that angles are counted in the right order
        j_ang = 1 / j_ang;
        p_ang = 1 / p_ang;
        
        //actual quicksort swapping
        if(j_ang > p_ang) {
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
    addLine(new Line(this->points[0]->x, this->points[0]->y, this->points[1]->x, this->points[1]->y, sf::Color(255, 0, 0, 255)));
    
    s->push(this->points[0]);
    s->push(this->points[1]);
    
    this->gRecurse(s,i);
}

void Plane::gRecurse(std::stack<Point*>* s, int i) {
    //initial condition: i is the last in the point vector
    if(i == (this->points).size()-1) {
        return;
    }
    
    //draw blue line, push next point to stack
    addLine(new Line(s->top()->x, s->top()->y, this->points[i]->x, this->points[i]->y, sf::Color(0, 0, 255, 255)));
    s->push(this->points[i]);
    
    //check direction of turn using top 3 points of stack
    Point* p3 = s->top();
    s->pop();
    Point* p2 = s->top();
    s->pop();
    Point* p1 = s->top();
    
    float slope1 = (p2->y - p1->y) / (p2->x - p1->x);
    float slope2 = (p3->y - p2->y) / (p3->x - p2->x);
    slope1 = 1/slope1;
    slope2 = 1/slope2;
    
    s->push(p2);
    s->push(p3);
    
    
    //if left turn, call again with i+1
    if(slope2 / slope1) {
        this->gRecurse(s,i+1);
    }
    
    //if right turn, pop 2 off stack, remove their lines, keep i the same
    else {
        s->pop();
        s->pop();
        this->gRecurse(s,i);
    }
}
