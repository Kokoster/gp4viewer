//
//  Window.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>

class Window {
public:
    Window();
    ~Window();
    SDL_Window* getWindow() const;
    
    
    int getHeight();
    int getWidth();
    
private:
    SDL_Window* window;
    
    Window(const Window& window);
    void operator= (const Window& window);
};
