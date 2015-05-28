//
//  beat_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 25.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "beat_node.h"

#include "config.h"

Rect BeatNode::getPadding() {
    Rect maxRect(position.x, position.y, 0, STAFF_LINE_VERTICAL_PADDING);
    
    for (auto& child : children) {
        if (child->getPadding().size.w > maxRect.size.w) {
            maxRect.size.w = child->getPadding().size.w + CHORD_MARGIN;
        }
    }
    
    return maxRect;
}