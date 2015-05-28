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

void MeasureNode::renderSelf(Renderer& renderer) {
    renderer.setColor(0, 0, 0, 255);
    
    int x = getGlobalPosition().x + getPadding().size.w;
    
    renderer.drawLine(x - 5, getGlobalPosition().y, x - 5, getGlobalPosition().y + 5 * STAFF_LINE_VERTICAL_PADDING);
}

Rect MeasureNode::getPadding() {
    Rect rect(position.x, position.y, CHORD_MARGIN, 5 * STAFF_LINE_VERTICAL_PADDING);

    for (auto& child : children) {
        if (child->getPadding().size.w > 0) {
            rect.size.w += child->getPadding().size.w;
        }
    }
    
    
    if (rect.size.w == CHORD_MARGIN) {
        rect.size.w = CHORD_MARGIN * 3;
    }

    return rect;
}