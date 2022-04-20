#include "Plane.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

Plane::Plane(char importMode) {
}

void Plane::sortPoints() {
    //finds the bottom left point
    Point* min = this->points[0];
    int min_idx = 0;
    for(int i=0; i<points.size(); i++) {
        if(points[i]->y < min->y) {
            if(points[i]->x <= min->x) {
                min = points[i];
                min_idx = i;
            }
        }
    }
    //switches the bottom left point to first in the vector
    Point* temp = this->points[0];
    this->points[0] = this->points[i];
    this->points[i] = temp;
    
    //calls a quicksort function to sort the vector relative to the min
    this->sortRecurse(1,this->points.size());
}

void Plane::sortRecurse(int low, int high) {
    //quick sort, orders all points based on their angle from the min point
    if(low < high) {
        part_idx = this->sortPartition(low,high);
        
        this->sortRecurse(low,part_idx-1);
        this->sortRecurse(part_idx+1,high);
    }
}

void Plane::sortPartition(int low, int high) {
    pivot = this->points[high];
    i = low - 1;
    int j_ang, p_ang;
    
    for(int j=low; j<high; j++) {
        //calculations to see whether j or pivot has the higher angle
        Point* j_point = this->points[j];
        Point* base = this->points[0];
        float j_ang = (j_point->y - base->y) / (j_point->x - base->x);
        float p_ang = (pivot->y - base->y) / (pivot->x - base->x);
        //flips all the negative slopes so that angles are counted in the right order
        if(j_ang < 0) {j_ang = 1 / j_ang;}
        if(p_ang < 0) {p_ang = 1 / p_ang;}
        
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
    Point* temp = this->points[high];
    this->points[i] = this->points[high];
    this->points[high] = temp;
    return i;
}

void Plane::addPoint(Point* p, unsigned int x, unsigned int y) {
}

void Plane::gScan(std::stack<Point*>* s) {
}