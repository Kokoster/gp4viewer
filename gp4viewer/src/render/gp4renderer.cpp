//
//  gp4renderer.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 05.04.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "gp4renderer.h"

#include <iostream>

#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>

GP4Renderer::GP4Renderer(Renderer* renderer, Window* window): textRenderer(*renderer) {
    this->renderer = renderer;
    this->window = window;

    currentLineY = 0;
    currentBeatX = CHORD_MARGIN;
//    currentNoteY = (STAFF_PADDING_KOEF - 1) * STAFF_LINE_VERTICAL_PADDING;
    
    tabsVerticalPadding = STAFF_LINE_VERTICAL_PADDING / 2;
    
    maxTabWidth = 0;
}

void GP4Renderer::renderGP4Data(const GP4Data& gp4Data) {
    renderer->setColor(255, 255, 255, 255);
    renderer->clear();
    
    drawNextStaff();
    for (int i = 0; i < 43; i++) {
        drawAllTabs(gp4Data.beats[i]);
    }
}

void GP4Renderer::drawAllTabs(const std::vector<std::vector<Beat>>& beats) {
    if (currentBeatX + beats[2].size() * CHORD_MARGIN + 15 * beats[2].size() + 5 > window->getWidth() - STAFF_LINE_HORIZONTAL_PADDING) {
        drawNextStaff();
    }
    
//    for (int i = 0; i < beats.size(); ++i) {
//        drawNextMeasure(beats[i]);
//    }
    
    drawNextMeasure(beats[2]);
}

void GP4Renderer::drawNextStaff() {
    renderer->setColor(0, 0, 0, 255);
    
    currentBeatX = STAFF_LINE_HORIZONTAL_PADDING;
    
    int x1 = STAFF_LINE_HORIZONTAL_PADDING ;
    int x2 = window->getWidth() - STAFF_LINE_HORIZONTAL_PADDING;
    currentLineY += STAFF_PADDING_KOEF * STAFF_LINE_VERTICAL_PADDING;
    
    firstLine = currentLineY - STAFF_LINE_VERTICAL_PADDING;
    
    for (int i = 0; i < 6; ++i) {
        renderer->drawLine(x1, currentLineY, x2, currentLineY);
    
        currentLineY += STAFF_LINE_VERTICAL_PADDING;
    }
    
    renderVerticalText("TAB");
    currentBeatX += CHORD_MARGIN;
}

void GP4Renderer::renderVerticalText(std::string text) {
    int tempY = firstLine + 2 * STAFF_LINE_VERTICAL_PADDING;
    SDL_Color color {0, 0, 0, 255};
    
    for (int i = 0; i < text.size(); ++i) {
        std::string c(sizeof(char), text[i]);
        textRenderer.renderText(c, currentBeatX, tempY, 13, color);
        
        tempY += STAFF_LINE_VERTICAL_PADDING;
    }
}

void GP4Renderer::drawNextMeasure(const std::vector<Beat>& beats) {
    for (int i = 0; i < beats.size(); ++i) {
        drawNextBeat(beats[i]);
    }
    
    currentBeatX += CHORD_MARGIN;
    
    int lastLine = firstLine + 6 * STAFF_LINE_VERTICAL_PADDING;
    renderer->drawLine(currentBeatX, firstLine + STAFF_LINE_VERTICAL_PADDING, currentBeatX, lastLine);
    
    maxTabWidth = 0;
}

void GP4Renderer::drawNextBeat(const Beat& beat) {
//    std::cout << "drawing beat" << std::endl;
    
    currentBeatX += maxTabWidth + CHORD_MARGIN;
    maxTabWidth = 0;

    currentNoteY = firstLine + tabsVerticalPadding;
    
    if (beat.chord.firstStr) {
        drawNote(beat.notes[5]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.secondStr) {
        drawNote(beat.notes[4]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.thirdStr) {
        drawNote(beat.notes[3]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.fourthStr) {
        drawNote(beat.notes[2]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.fifthStr) {
        drawNote(beat.notes[1]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.sixthStr) {
        drawNote(beat.notes[0]);
    }
    
    if (maxTabWidth == 0) {
        currentBeatX += CHORD_MARGIN;
    }
}

void GP4Renderer::drawNote(const Note& note) {
//    std::cout << "drawing note" << std::endl;
    
    SDL_Color color {0, 0, 0, 255};
    
    if ((int) note.type == 3) {
        // dead note
        std::string fret = "X";
        int temp = textRenderer.renderText(fret, currentBeatX, currentNoteY, 11, color);
        
        if (temp > maxTabWidth) {
            maxTabWidth = temp;
        }
        
        return;
    }

    if ((int) note.type == 2) {
        // tie note
        return;
    }
    
    char c[3];
    snprintf(c, 2, "%d", note.fretNumber);
    std::string fret = c;
    
    if (note.header.ghostNote) {
        fret.insert(fret.begin(), '(');
        fret.insert(fret.end(), ')');
    };
    
//    std::cout << "fret: " << fret << std::endl;
    
    int temp = textRenderer.renderText(fret, currentBeatX, currentNoteY, 11, color);
    
    if (temp > maxTabWidth) {
        maxTabWidth = temp;
    }
    
    return;
}
