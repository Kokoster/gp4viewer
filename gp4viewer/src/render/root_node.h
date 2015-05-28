//
//  rootNode.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "node.h"

#include "window.h"
#include "renderer.h"

#include "gp4data.h"

class RootNode : public Node {
public:
    RootNode(Renderer* renderer, Window* window);
    
    void calculateEverything(const GP4Data& gp4Data);
    
private:
    Window* window;
    Renderer* renderer;
    
    bool hasMeasure;
    int currentIndex;
    
    void setMeasureNode(Node* rowStaff, std::unique_ptr<Node>& measureNode, const GP4Data& gp4Data);
//    void setTabNode(std::unique_ptr<Node>& staffNode);
    void setTabNode(Node* staffNode);
    void setNoteNode(std::unique_ptr<Node>& beatNode, Beat beat);
};
