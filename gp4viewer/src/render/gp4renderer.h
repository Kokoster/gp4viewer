//
//  gp4renderer.h
//  gp4viewer
//
//  Created by Ольга Диденко on 05.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#pragma once

#include <vector>

#include "window.h"
#include "renderer.h"

#include "gp4data.h"

#include "text_renderer.h"

class GP4Renderer {
public:
    GP4Renderer(Renderer* renderer, Window* window);
    
    GP4Renderer(const GP4Renderer& renderer) = delete;
    const GP4Renderer& operator=(const GP4Renderer& renderer) = delete;
    
    void renderGP4Data(const GP4Data& gp4Data, int yDelta);
    
private:
    const int STAFF_LINE_HORIZONTAL_PADDING = 20;
    const int STAFF_LINE_VERTICAL_PADDING = 11;
    const int STAFF_PADDING_KOEF = 3;
    const int CHORD_MARGIN = 20;
    
    int yInit;
    
    int currentBeatX;
    int currentLineY;
    int currentNoteY;
    
    int firstLine;
    
    Renderer* renderer;
    Window* window;

    void drawAllTabs(const std::vector<std::vector<Beat>>& beats);
    void drawNextStaff();
    void drawNextMeasure(const std::vector<Beat>& beats);
    void drawNextBeat(const Beat& beat);
    void drawChord(Chord chord);
    void drawNote(const Note& note);
    
    int maxTabWidth;
    
    void renderVerticalText(std::string text);
    
    TextRenderer textRenderer;
};
