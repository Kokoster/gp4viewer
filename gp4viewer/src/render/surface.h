//
//  Surface.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>
#include <string>


class Surface {
public:
    Surface(SDL_Surface* surface);
    Surface(const std::string& string);
    ~Surface();
    
    Surface(const Surface& surface) = delete;
    void operator= (const Surface& surface) = delete;
    
    SDL_Surface* getSurface() const;
private:
    SDL_Surface* surface;
};


