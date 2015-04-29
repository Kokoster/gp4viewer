//
//  Renderer.h
//  TestSDL2
//
//  Created by Stanislav Krasnoyarov on 22/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "renderer.h"

Renderer::Renderer(const Window& window) {
    renderer = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

SDL_Renderer* Renderer::getRenderer() const {
    return renderer;
}

void Renderer::copy(SDL_Texture* texture, const SDL_Rect& rect) const {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Renderer::present() const {
    SDL_RenderPresent(renderer);
}
    
int Renderer::getWidth() const {
    int w;
    SDL_GetRendererOutputSize(renderer, &w, NULL);
    
    return w;
}
    
int Renderer::getHeight() const {
    int h;
    SDL_GetRendererOutputSize(renderer, NULL, &h);
    
    return h;
}

void Renderer::clear() {
    SDL_RenderClear(renderer);
}

void Renderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

