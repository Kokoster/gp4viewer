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

class Texture;

class Renderer {
public:
    Renderer(const Window& window);
    ~Renderer();
    
    Renderer(const Renderer& renderer) = delete;
    void operator= (const Renderer& renderer) = delete;
    
    SDL_Renderer* getRenderer() const;
    void copy(SDL_Texture* texture, const SDL_Rect& rect) const;
    void present() const;
    
    int getWidth() const;
    int getHeight() const;
    
    void clear();
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawLine(int x1, int y1, int x2, int y2);

private:
    SDL_Renderer* renderer;
};