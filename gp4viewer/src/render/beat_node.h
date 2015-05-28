//
//  beat_node.h
//  gp4viewer
//
//  Created by Ольга Диденко on 25.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include "node.h"

class BeatNode : public Node {
public:
//    virtual void renderSelf();
    
    virtual Rect getPadding();
};