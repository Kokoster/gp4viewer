//
//  node.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "node.h"

#include "config.h"

Node::Node() {
    parent = nullptr;
}

void Node::addChild(std::unique_ptr<Node>& child) {
    child->parent = this;
    children.push_back(move(child));
}

void Node::removeChild(Node* child) {
    auto it = find_if(children.begin(), children.end(),[&child](const std::unique_ptr<Node>& currentNode){ return currentNode.get() == child; });
    
    children.erase(it);
}

const std::vector<std::unique_ptr<Node>>& Node::getChildren() {
    return children;
}

Node* Node::getParent() {
    return parent;
}

Point Node::getGlobalPosition() {
    if (parent) {
        return parent->getGlobalPosition() + position;
    }
    
    return position;
}

void Node::setPosition(const Point& position) {
    this->position = position;
}

Point Node::getPosition() {
    return position;
}

void Node::render(Renderer& renderer) {
    renderSelf(renderer);
    
    for (auto& child : children) {
        child->render(renderer);
    }
}

void Node::renderSelf(Renderer& renderer) {
    
}

Rect Node::getPadding() {
    Rect rect(position.x, position.y, 0, 50);
    
    for (auto& child : children) {
        rect.size.w += child->getPadding().size.w;
        rect.size.h += child->getPadding().size.h;
    }
    
    return rect;
}

Rect Node::getLinePadding() {
    if (parent != NULL) {
        return parent->getLinePadding();
    }
    else {
        Rect rect(position.x, position.y, 0, 0);
        return rect;
    }
}

int Node::getHeight() {
    int height = 0;
    
    if (children.size()) {
        height = children[0]->getHeight();
    }
    
    return height;
}
