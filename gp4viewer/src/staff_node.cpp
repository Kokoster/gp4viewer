//
//  staff_node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "staff_node.h"

#include "text_node.h"

TabStaffNode::TabStaffNode(Window& window, int verticalPadding) {
    position.x = STAFF_LINE_HORIZONTAL_PADDING;
    position.y = verticalPadding;
    
    windowWidth = window.getWidth();
}

void TabStaffNode::renderSelf(Renderer& renderer) {
    renderer.setColor(0, 0, 0, 255);

    int lastX = windowWidth - STAFF_LINE_HORIZONTAL_PADDING;
    
    int lineY = getGlobalPosition().y;
    
    for (int i = 0; i < 5; ++i) {
        renderer.drawLine(getGlobalPosition().x, lineY, lastX, lineY);
        lineY += TAB_STAFF_LINE_VERTICAL_PADDING;
    }
    renderer.drawLine(position.x, lineY, lastX, lineY);
    
    lineY = getGlobalPosition().y;
    
    renderer.drawLine(getGlobalPosition().x, lineY, getGlobalPosition().x, lineY + TAB_STAFF_LINE_VERTICAL_PADDING * 5);
}


Rect TabStaffNode::getPadding() {
    Rect rect(position.x, position.y, 0, TAB_STAFF_LINE_VERTICAL_PADDING * 5 + 2 * STAFF_PADDING_KOEF);
    
    for (auto& child : children) {
        rect.size.w += child->getPadding().size.w;
    }
    
    rect.size.w += CHORD_MARGIN;
    
    return rect;
}

int TabStaffNode::getHeight() {
    return 5 * TAB_STAFF_LINE_VERTICAL_PADDING;
}

Rect TabStaffNode::getLinePadding() {
    Rect rect(position.x, position.y, 0, TAB_STAFF_LINE_VERTICAL_PADDING);
    return rect;
}

NoteStaffNode::NoteStaffNode(Window& window, int verticalPadding) {
    position.x = STAFF_LINE_HORIZONTAL_PADDING;
    position.y = verticalPadding;
    
    windowWidth = window.getWidth();
}

void NoteStaffNode::renderSelf(Renderer& renderer) {
    renderer.setColor(0, 0, 0, 255);
    
    int lastX = windowWidth - STAFF_LINE_HORIZONTAL_PADDING;
    
    int lineY = getGlobalPosition().y;
    
    for (int i = 0; i < 4; ++i) {
        renderer.drawLine(getGlobalPosition().x, lineY, lastX, lineY);
        lineY += NOTE_STAFF_LINE_VERTICAL_PADDING;
    }
    renderer.drawLine(position.x, lineY, lastX, lineY);
    
    lineY = getGlobalPosition().y;
    
    renderer.drawLine(getGlobalPosition().x, lineY, getGlobalPosition().x, lineY + NOTE_STAFF_LINE_VERTICAL_PADDING * 4);
}

Rect NoteStaffNode::getPadding() {
    Rect rect(position.x, position.y, 0, 4 * NOTE_STAFF_LINE_VERTICAL_PADDING + GENERAL_STAFF_PADDING);
    
    for (auto& child : children) {
        rect.size.w += child->getPadding().size.w;
    }
    
    rect.size.w += CHORD_MARGIN;
    
    return rect;
}

Rect NoteStaffNode::getLinePadding() {
    Rect rect(position.x, position.y, 0, NOTE_STAFF_LINE_VERTICAL_PADDING);
    return rect;
}

int NoteStaffNode::getHeight() {
    return 4 * NOTE_STAFF_LINE_VERTICAL_PADDING;
}



