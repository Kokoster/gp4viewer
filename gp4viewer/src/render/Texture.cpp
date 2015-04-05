//
//  Texture.cpp
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#include "Texture.h"

namespace pacman {

Texture::Texture(const Renderer& renderer, const Surface& surface) {
    texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface.getSurface());
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture() const {
    return texture;
}
}