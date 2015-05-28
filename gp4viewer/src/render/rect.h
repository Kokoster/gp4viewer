//
//  Rect.h
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include "point.h"
#include "size.h"
    
class Rect {
public:
    Rect() {};
    Rect(const Point& position, const Size& size);
    Rect(int x, int y, int w, int h);
    
    void setPosition(Point position) { this->position = position; };
    Point getPosition() const        { return position; };
    
    void setSize(Size size)          { this->size = size; };
    Size getSize() const             { return size; };
    
    bool intersects(const Rect& other) const;
    
    Point position;
    Size size;
};


