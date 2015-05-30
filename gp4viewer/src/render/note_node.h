//
//  note_node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 30.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "node.h"

#include "texture.h"
#include "rect.h"

class NoteNode : public Node {
public:
    NoteNode(const Renderer& renderer, const std::string& image);
    virtual void renderSelf(Renderer& renderer);
    virtual Rect getPadding();
    
private:
    std::unique_ptr<Texture> texture;
};
