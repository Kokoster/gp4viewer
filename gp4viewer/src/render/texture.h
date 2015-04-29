//
//  Texture.h
//  TestSDL2
//
//  Created by Ольга Диденко on 23/11/14.
//  Copyright (c) 2014 Stanislav Krasnoyarov. All rights reserved.
//

#pragma once

#include <SDL2/SDL.h>

#include "renderer.h"
#include "surface.h"

class Texture {
public:
    Texture(const Renderer& renderer, const Surface& surface);
    ~Texture();
    
    Texture(const Texture& texture) = delete;
    void operator= (const Texture& texture) = delete;
    
    SDL_Texture* getTexture() const;
private:
    SDL_Texture* texture;
};
