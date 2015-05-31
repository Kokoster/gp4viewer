//
//  node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include <vector>

#include "renderer.h"

#include "point.h"
#include "rect.h"

class Node {
public:
    Node();
//    virtual ~Node();
    
    Node(const Node& node) = delete;
    Node& operator=(const Node& node) = delete;
    
    virtual void render(Renderer& renderer);
    virtual void renderSelf(Renderer& renderer);
    virtual void addChild(std::unique_ptr<Node>& child);
    virtual void removeChild(Node* child);
    virtual const std::vector<std::unique_ptr<Node>>& getChildren();
    
    virtual Point getGlobalPosition();
    virtual Node* getParent();
    
    virtual void setPosition(const Point& position);
    virtual Point getPosition();
    
    virtual Rect getPadding();
    virtual Rect getLinePadding();
    
    virtual int getHeight();
    
    virtual void setPadding(int padding);
    
protected:
    Node* parent;
    std::vector<std::unique_ptr<Node>> children;
    
    int padding;
    
    Point position;
};
