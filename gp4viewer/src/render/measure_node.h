//
//  measure_node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "node.h"

#include "renderer.h"
#include "point.h"

class MeasureNode : public Node {
public:
    virtual void renderSelf(Renderer& renderer);
    virtual Rect getPadding();
};