//
//  Renderer.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "sdl.h"

#include <iostream>

SDL::SDL() {
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        std::cout << "ERROR SDL_Init" << std::endl;
//        return;
//    }
    SDL_Init(SDL_INIT_EVERYTHING);
    
//    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
//        std::cout << "ERROR IMG_Init" << std::endl;
//        return -1;
//    }
    
//    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

SDL::~SDL() {
//    IMG_Quit();
    SDL_Quit();
}

