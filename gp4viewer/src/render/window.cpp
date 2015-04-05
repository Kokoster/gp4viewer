//
//  Window.cpp
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "Window.h"


Window::Window() {
    window = SDL_CreateWindow("SDL 2 window",             // window title
                              SDL_WINDOWPOS_CENTERED,     // x position, centered
                              SDL_WINDOWPOS_CENTERED,     // y position, centered
                              600,                        // width, in pixels
                              660,                        // height, in pixels
                              SDL_WINDOW_OPENGL           // flags
                              );

}

Window::~Window() {
    SDL_DestroyWindow(window);
}

SDL_Window* Window::getWindow() const {
    return window;
}

int Window::getHeight() {
    int h;
    
    SDL_GetWindowSize(window, NULL, &h);
    
    return h;
}

int Window::getWidth() {
    int w;
    
    SDL_GetWindowSize(window, &w, NULL);
    
    return w;
}
