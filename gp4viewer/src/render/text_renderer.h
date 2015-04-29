//
//  text_renderer.h
//  gp4viewer
//
//  Created by Ольга Диденко on 18.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "renderer.h"

class TextRenderer {
public:
    TextRenderer(const Renderer& renderer);
    
    void renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color);
    
private:
    const Renderer& renderer;
};
