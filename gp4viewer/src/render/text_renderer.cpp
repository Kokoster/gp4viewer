//
//  text_renderer.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 18.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "text_renderer.h"

#include <iostream>

#include <SDL2_ttf/SDL_ttf.h>

#include "texture.h"
#include "surface.h"
#include "rect.h"

TextRenderer::TextRenderer(const Renderer& _renderer) : renderer(_renderer) {
        TTF_Init();
}

int TextRenderer::renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color) {
    
    //Open the font
    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", fontSize);
    if (font == nullptr){
        std::cout << TTF_GetError() << std::endl;
        return -1;
    }
    
//    SDL_Surface* sdlSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Color bgColor = {255, 255, 255, 255};
    
    SDL_Surface* sdlSurface;
    for (int i = 0; i < text.size(); ++i) {
        sdlSurface = TTF_RenderText_Shaded(font, text.c_str(), color, bgColor);
        
        if (sdlSurface == nullptr){
            TTF_CloseFont(font);
            return -1;
        }
        
        Surface surface(sdlSurface);

        Texture texture(renderer, surface);

        SDL_Rect rect {x, y, sdlSurface->w, sdlSurface->h};
    //    SDL_Rect rect {x, y, fontSize, fontSize};
        
        renderer.copy(texture.getTexture(), rect);
    }

    TTF_CloseFont(font);
    
    return (sdlSurface->w - 1);
}
