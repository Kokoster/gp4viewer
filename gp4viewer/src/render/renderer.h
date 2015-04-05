//
//  Renderer.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>

#include "window.h"

class Renderer {
public:
    Renderer(const Window& window);
    ~Renderer();
    
    Renderer(const Renderer& renderer) = delete;
    void operator= (const Renderer& renderer) = delete;
    
    SDL_Renderer* getRenderer() const;
    void clear() const;
    void copy(SDL_Texture* texture, const SDL_Rect& rect) const;
    void present() const;
    
    int getWidth() const;
    int getHeight() const;

private:
    SDL_Renderer* renderer;
};