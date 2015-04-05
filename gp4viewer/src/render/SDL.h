//
//  SDL.h
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
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
