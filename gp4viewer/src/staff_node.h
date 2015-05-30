//
//  staff_node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "node.h"
#include "renderer.h"
#include "window.h"

#include "config.h"

//class StaffNode : public Node {
//public:
//    StaffNode(Window& window, int verticalPadding);
//    virtual void renderSelf(Renderer& renderer);
//    virtual Rect getPadding();
//    
//private:
//    int windowWidth;
//};

class TabStaffNode : public Node {
public:
    TabStaffNode(Window& window, int verticalPadding);
    virtual void renderSelf(Renderer& renderer);
    virtual Rect getPadding();
    virtual Rect getLinePadding();
    virtual int getHeight();
    
private:
    int windowWidth;
};

class NoteStaffNode : public Node {
public:
    NoteStaffNode(Window& window, int verticalPadding);
    virtual void renderSelf(Renderer& renderer);
    virtual Rect getPadding();
    virtual Rect getLinePadding();
    virtual int getHeight();
    
private:
    int windowWidth;
};