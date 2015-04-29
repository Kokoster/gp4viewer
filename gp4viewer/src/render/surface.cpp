//
//  Surface.cpp
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "surface.h"

Surface::Surface(SDL_Surface* surface) {
    this->surface = surface;
}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface* Surface::getSurface() const {
    return surface;
}


