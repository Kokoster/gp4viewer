//
//  text_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "text_node.h"

#include <iostream>

#include <SDL2_ttf/SDL_ttf.h>

#include "texture.h"
#include "surface.h"
#include "rect.h"

#include "config.h"

TextNode::TextNode(const Renderer& renderer, const std::string& text, int fontSize) {
    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", fontSize);
    if (font == nullptr){
        std::cout << TTF_GetError() << std::endl;
        return;
    }
    
    SDL_Color bgColor = {255, 255, 255, 255};
    SDL_Color color = {0, 0, 0, 255};
    
    SDL_Surface* sdlSurface;
    
    sdlSurface = TTF_RenderText_Shaded(font, text.c_str(), color, bgColor);
        
    if (sdlSurface == nullptr) {
        TTF_CloseFont(font);
        return;
    }
        
    Surface surface(sdlSurface);
        
    texture = std::unique_ptr<Texture>(new Texture(renderer, surface));

    TTF_CloseFont(font);
}

void TextNode::renderSelf(Renderer& renderer) {
    if (texture == NULL) {
//        SDL_Rect rect {getGlobalPosition().x, getGlobalPosition().y, CHORD_MARGIN, STAFF_LINE_VERTICAL_PADDING};
//        
//        renderer.copy(texture->getTexture(), rect);
        return;
    }
    
    SDL_Rect rect {getGlobalPosition().x, getGlobalPosition().y, texture->getWidth(), texture->getHeight()};
    renderer.copy(texture->getTexture(), rect);
}

Rect TextNode::getPadding() {
    if (texture == NULL) {
        Rect rect(position.x, position.y, 0, 5 * STAFF_LINE_VERTICAL_PADDING);
        
        return rect;
    }
    
    Rect rect(position.x, position.y, texture->getWidth(), 5 * STAFF_LINE_VERTICAL_PADDING);
    
    return rect;
}