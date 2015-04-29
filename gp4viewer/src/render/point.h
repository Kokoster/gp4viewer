//
//  Point.h
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

class Point {
public:
    Point();
    Point(int x, int y);
    
    void setX(int x) { this->x = x; };
    int getX() const { return x; };
    
    void setY(int y) { this->y = y; };
    int getY() const { return y; };
    
private:
    int x, y;
};

