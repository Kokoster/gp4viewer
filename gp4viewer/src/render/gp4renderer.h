//
//  gp4renderer.h
//  gp4viewer
//
//  Created by Ольга Диденко on 05.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "window.h"
#include "renderer.h"

#include "gp4data.h"

class GP4Renderer {
public:
    GP4Renderer(Renderer* renderer, Window* window);
    
    GP4Renderer(const GP4Renderer& renderer) = delete;
    const GP4Renderer& operator=(const GP4Renderer& renderer) = delete;
    
    void renderGP4Data(const GP4Data& gp4Data);
    
private:
    const int STAFF_LINE_VERTICAL_PADDING = 10;
    
    Renderer* renderer;
    Window* window;
    
    void drawStaff();
};