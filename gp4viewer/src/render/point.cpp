//
//  Point.cpp
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//


#include "point.h"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point& Point::operator=(const Point& point) {
    x = point.x;
    y = point.y;
    
    return *this;
}

Point Point::operator+(const Point& point) {
    Point temp;
    
    temp.x = x + point.x;
    temp.y = y + point.y;
    
    return temp;
}

Point Point::operator-(const Point& point) {
    Point temp;
    
    temp.x = x - point.x;
    temp.y = y - point.y;
    
    return temp;
}

