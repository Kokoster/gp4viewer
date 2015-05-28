//
//  Texture.cpp
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "texture.h"

Texture::Texture(const Renderer& renderer, const Surface& surface) {
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface.getSurface());
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}

int Texture::getWidth() {
    return w;
}

int Texture::getHeight() {
    return h;
}
