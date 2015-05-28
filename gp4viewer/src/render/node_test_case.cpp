//
//  node_test_case.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "node_test_case.h"

#include <iostream>

#include "node.h"
#include "point.h"

template <typename T>
void assertEquals(const T& expected, const T& actual) {
    if (expected != actual) {
        std::cout << "Failed, expected: " << expected << std::endl
                  << "          actual: " << actual   << std::endl;
    } else {
        std::cout << "Ok" << std::endl;
    }
}

void testAddRemoveChild() {
    std::cout << "testAddRemoveChild" << std::endl;
    
    Node parentNode;
    
    assertEquals<size_t>(0, parentNode.getChildren().size());
    
    
    std::unique_ptr<Node> childNode(new Node);
    Node* rawChild = childNode.get();
    parentNode.addChild(childNode);
    
    assertEquals<size_t>(1, parentNode.getChildren().size());
    assertEquals(&parentNode, rawChild->getParent());
    
    parentNode.removeChild(rawChild);
    assertEquals<size_t>(0, parentNode.getChildren().size());
    assertEquals<Node*>(nullptr, rawChild->getParent());
}

void testPosition() {
    std::cout << "testPosition" << std::endl;
    
    Node parentNode;
    
    Point position(1, 2);
    parentNode.setPosition(position);
    assertEquals(1, parentNode.getGlobalPosition().x);
    assertEquals(2, parentNode.getGlobalPosition().y);
    
    std::unique_ptr<Node> childNode(new Node);
    position.x = 2;
    position.y = 3;
    childNode->setPosition(position);
    Node* rawChild = childNode.get();
    parentNode.addChild(childNode);
    
    assertEquals(3, rawChild->getGlobalPosition().x);
    assertEquals(5, rawChild->getGlobalPosition().y);
}

void runTests() {
    testAddRemoveChild();
    testPosition();
}
