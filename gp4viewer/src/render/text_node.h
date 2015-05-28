//
//  text_node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include <string>

#include "texture.h"

#include "node.h"

class TextNode : public Node {
public:
    TextNode(const Renderer& renderer, const std::string& text, int fontSize);
    
    virtual void renderSelf(Renderer& renderer);
    
    virtual Rect getPadding();
    
private:
    std::unique_ptr<Texture> texture;
};