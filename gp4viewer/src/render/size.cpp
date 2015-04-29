//
//  Size.cpp
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "size.h"

Size::Size() {
    w = 0;
    h = 0;
}

Size::Size(int w, int h) {
    this->w = w;
    this->h = h;
}