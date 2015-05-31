//
//  note_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 30.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "note_node.h"

#include <string>
#include <iostream>

#include "surface.h"

NoteNode::NoteNode(const Renderer& renderer, const std::string& image) {
    Surface noteSurface(image);
    texture = std::unique_ptr<Texture>(new Texture(renderer, noteSurface));
}

void NoteNode::renderSelf(Renderer& renderer) {
    SDL_Rect rect {getGlobalPosition().x, getGlobalPosition().y, texture->getWidth(), texture->getHeight()};
    
    renderer.copy(texture->getTexture(), rect);
}

Rect NoteNode::getPadding() {
    Rect rect(position.x, position.y, 0, 0);
    
    rect.size.w = texture->getWidth();
    rect.size.h = texture->getHeight();
    
    return rect;
}