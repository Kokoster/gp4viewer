//
//  Rect.cpp
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "rect.h"

Rect::Rect(const Point& position, const Size& size) :
    position(position),
    size(size)
{
}


Rect::Rect(int x, int y, int w, int h) :
    position(x, y),
    size(w, h)
{
}

bool Rect::intersects(const Rect& other) const {
    return position.getX() <= other.position.getX() + other.size.getWidth() &&
           position.getX() + size.getWidth() >= other.position.getX() &&
           position.getY() <= other.position.getY() + other.size.getHeight() &&
           position.getY() + size.getHeight() >= other.position.getY();
}