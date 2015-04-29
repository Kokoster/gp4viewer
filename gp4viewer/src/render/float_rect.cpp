//
//  float_rect.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 27.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "float_rect.h"

FloatRect::FloatRect(const Point& position, const Size& size) :
position(position),
size(size)
{
}


FloatRect::FloatRect(float x, float y, float w, float h) :
position(x, y),
size(w, h)
{
}