//
//  Size.h
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

class Size {
public:
    Size();
    Size(int w, int h);
    
    void setWidth(int w) { this->w = w; };
    int getWidth() const { return w; };
    
    void setHeight(int h) { this->h = h; };
    int getHeight() const { return h; };
    
    int w, h;
};

