//
//  staff_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "staff_node.h"

#include "text_node.h"

StaffNode::StaffNode(Window& window, int verticalPadding) {
    position.x = STAFF_LINE_HORIZONTAL_PADDING;
    position.y = verticalPadding;
    
    windowWidth = window.getWidth();
}

void StaffNode::renderSelf(Renderer& renderer) {
    renderer.setColor(0, 0, 0, 255);

    int lastX = windowWidth - STAFF_LINE_HORIZONTAL_PADDING;
    
    int lineY = getGlobalPosition().y;
    
    for (int i = 0; i < 5; ++i) {
        renderer.drawLine(getGlobalPosition().x, lineY, lastX, lineY);
        lineY += STAFF_LINE_VERTICAL_PADDING;
    }
    renderer.drawLine(position.x, lineY, lastX, lineY);
    
    lineY = getGlobalPosition().y;
    
    renderer.drawLine(getGlobalPosition().x, lineY, getGlobalPosition().x, lineY + STAFF_LINE_VERTICAL_PADDING * 5);
}


Rect StaffNode::getPadding() {
    Rect rect(position.x, position.y, 0, 5 * STAFF_LINE_VERTICAL_PADDING);
    
    for (auto& child : children) {
        rect.size.w += child->getPadding().size.w;
    }
    
    rect.size.w += CHORD_MARGIN;
    
    return rect;
}

