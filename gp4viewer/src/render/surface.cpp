//
//  Surface.cpp
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "surface.h"

#include <SDL2_image/SDL_image.h>

Surface::Surface(SDL_Surface* surface) {
    this->surface = surface;
}

Surface::Surface(const std::string& name) {
    surface = IMG_Load(name.c_str());
}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

SDL_Surface* Surface::getSurface() const {
    return surface;
}



