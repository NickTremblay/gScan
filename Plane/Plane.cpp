#include "Plane.h"
#include "../Line/Line.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

Plane::Plane(int w, int h) {
    _width = w;
    _height = h;
}

Plane::~Plane(){
    // Deallocate all class objects from heap memory
    for(int i = 0; i < points.size(); i++){
        delete points[i];
    }
    
    for(int k = 0; k < lines.size(); k++){
        delete lines[k];
    }
    
}

bool Plane::sortPoints() {
    //finds the bottom-most point
    Point* min = this->points[0];
    int min_idx = 0;
    for(int i=0; i<points.size(); i++) {
        if((_height - (points[i]->y) < (_height - (min->y)))){
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
    
    for(int i = 1; i < points.size(); i++){
        double angle;
        angle = std::atan2((_height - points[i]->y) - (_height - points[0]->y), points[i]->x - points[0]->x);
        angle = angle * 180 / 3.14;
        //angle = 180 - angle;
        points[i]->angle = angle;
    }
    
    // sort points by angle
    int i, j;
    
    // Temp var for sort comparison
    Point* t;
    
    for (i = 1; i < points.size(); i++){
        t = points[i];
        j = i - 1;
 
        while (j >= 0 && points[j]->angle > t->angle)
        {
            points[j + 1] = points[j];
            j -= 1;
        }
        points[j + 1] = t;
    }
    
    //std::sort(this->points.begin() + 1, this->points.end());

    /*std::cout << "Sorted points" << std::endl;
    for(int k = 0; k < this->points.size(); k++){
        std::cout << this->points[k]->x << "," << this->points[k]->y << " " << this->points[k]->angle << std::endl;
    }*/
    
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
    
    return (sortedPoints.size() >= 3);
}

void Plane::addPoint(Point* p) {
    points.push_back(p);
    
    if(p->x >= _width - 20){
        _width += 20;
    }
    
    if(p->y >= _height - 20){
        _height += 20;
    }
}

void Plane::addLine(Line* l){
    lines.push_back(l);
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
}

void Plane::gScan() {
    std::stack<Point*> s;
    //draws red line from start point to first point, pushes first 2 points to stack, sets counter i to 2
    int i = 2;
    addLine(new Line(this->sortedPoints[0]->x, this->sortedPoints[0]->y, this->sortedPoints[1]->x, this->sortedPoints[1]->y, sf::Color(255, 0, 0, 255)));
    
    s.push(this->sortedPoints[0]);
    s.push(this->sortedPoints[1]);
    
    this->gRecurse(&s,i);
}

void Plane::gRecurse(std::stack<Point*>* s, int i) {
    //draw blue line, push next point to stack
    addLine(new Line(s->top()->x, s->top()->y, this->sortedPoints[i]->x, this->sortedPoints[i]->y, sf::Color::Blue));
    s->push(this->sortedPoints[i]);
    
    //check direction of turn using top 3 points of stack
    Point* p3 = s->top();
    s->pop();
    Point* p2 = s->top();
    s->pop();
    Point* p1 = s->top();
    
    double slope1, slope2;
    slope1 = std::atan2(((_height - p2->y) - (_height - p1->y)), (p2->x - p1->x));
    slope2 = std::atan2(((_height - p3->y) - (_height - p2->y)), (p3->x - p2->x));
    if(slope1 < 0) {slope1 += 360;}
    if(slope2 < 0) {slope2 += 360;}
    
    
    s->push(p2);
    s->push(p3);
    
    //initial condition: i is the last in the point vector
    if(i == (this->sortedPoints).size()-1  && slope2 > slope1) {
        addLine(new Line(sortedPoints[i]->x, sortedPoints[i]->y, s->top()->x, s->top()->y, sf::Color::Red));
        addLine(new Line(p2->x,p2->y,p3->x,p3->y,sf::Color::Red));
        addLine(new Line(sortedPoints[0]->x, sortedPoints[0]->y, sortedPoints[i]->x, sortedPoints[i]->y, sf::Color::Red));
        
        return;
    }
    
    //if left turn, call again with i+1
    if(slope2 > slope1) {
        addLine(new Line(p2->x, p2->y, p3->x, p3->y, sf::Color::Red));
        this->gRecurse(s,i+1);
    }
    
    //if right turn, pop 2 off stack, remove their lines, keep i the same
    else {
        addLine(new Line(p2->x, p2->y, p3->x, p3->y, sf::Color::White));
        addLine(new Line(p1->x, p1->y, p2->x, p2->y, sf::Color::White));
        s->pop();
        s->pop();
        this->gRecurse(s,i);
    }
}

int Plane::getWidth(){
    return _width;
}

int Plane::getHeight(){
    return _height;
}

void Plane::setWidth(int w){
    _width = w;
}

void Plane::setHeight(int h){
    _height = h;
}
int Plane::getPointCount(){
    return points.size();
}

int Plane::getLineCount(){
    return lines.size();
}

Point* Plane::getPoint(int i){
    // Bounds check vector before accessing memory
    if(i > points.size() || i < 0){
        std::cout << "Error: Point " << i << " does not exist" << std::endl;
        return nullptr;
    }
    
    return points[i];
}

Line* Plane::getLine(int i){
    // Bounds check vector before accessing memory
    if(i > lines.size() || i < 0){
        std::cout << "Error: Line " << i << " does not exist" << std::endl;
        return nullptr;
    }
    
    return lines[i];
}
