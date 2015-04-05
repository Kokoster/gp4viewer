//
//  gp4renderer.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 05.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "gp4renderer.h"

GP4Renderer::GP4Renderer(Renderer* renderer, Window* window) {
    this->renderer = renderer;
    this->window = window;
}

void GP4Renderer::renderGP4Data(const GP4Data& gp4Data) {
    renderer->setColor(255, 255, 255, 255);
    renderer->clear();
    
    drawStaff();
}

void GP4Renderer::drawStaff() {
    renderer->setColor(0, 0, 0, 255);
    
    int x1 = 20;
    int x2 = window->getWidth() - 20;
    int y1 = 3 * STAFF_LINE_VERTICAL_PADDING;
    int y2 = 3 * STAFF_LINE_VERTICAL_PADDING;
    
    for (int i = 0; i < 6; ++i) {
        renderer->drawLine(x1, y1, x2, y2);
        
        y1 += STAFF_LINE_VERTICAL_PADDING;
        y2 += STAFF_LINE_VERTICAL_PADDING;
    }
}
