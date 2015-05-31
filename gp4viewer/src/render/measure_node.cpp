//
//  measure_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "measure_node.h"
#include <iostream>

#include "config.h"

MeasureNode::MeasureNode() {
    padding = 0;
}

void MeasureNode::renderSelf(Renderer& renderer) {
    renderer.setColor(0, 0, 0, 255);
    
    int x = getGlobalPosition().x + getPadding().size.w;
    
    renderer.drawLine(x, getGlobalPosition().y, x, getGlobalPosition().y + parent->getHeight());
    
//    std::cout << "measure: " << std::endl;
//    std::cout << getPosition().y << std::endl;
//    std::cout << getGlobalPosition().y << std::endl;
}

Rect MeasureNode::getPadding() {
    Rect rect(position.x, position.y, CHORD_MARGIN, 0);

    for (auto& child : children) {
        if (child->getPadding().size.w > 0) {
            rect.size.w += child->getPadding().size.w;
        }
    }
    
    
    if (rect.size.w == CHORD_MARGIN) {
        rect.size.w = CHORD_MARGIN * 3;
    }
    
    rect.size.w += padding;
    

    return rect;
}