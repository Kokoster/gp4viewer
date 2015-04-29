//
//  float_rect.h
//  gp4viewer
//
//  Created by Ольга Диденко on 27.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "point.h"
#include "size.h"

class FloatRect {
public:
    FloatRect() {};
    FloatRect(const Point& position, const Size& size);
    FloatRect(float x, float y, float w, float h);
    
    void setPosition(Point position) { this->position = position; };
    Point getPosition() const        { return position; };
    
    void setSize(Size size)          { this->size = size; };
    Size getSize() const             { return size; };
    
//    bool intersects(const FloatRect& other) const;
    
private:
    Point position;
    Size size;
};
