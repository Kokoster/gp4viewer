//
//  Renderer.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>

class SDL {
public:
    SDL();
    ~SDL();
    
    SDL(const SDL& sdl) = delete;
    void operator= (const SDL& sdl) = delete;
};
