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
    
    nextStaff = true;
}

void GP4Renderer::renderGP4Data(const GP4Data& gp4Data) {
    renderer->setColor(255, 255, 255, 255);
    renderer->clear();
    
//    SDL_Color color {0, 0, 0, 255};
//    textRenderer.renderText("3", 100, 100, 10, color);
    
    for (int i = 0; i < 25; i += STAFF_MEASURES_COUNT) {
        for (int j = i; j < i + STAFF_MEASURES_COUNT; ++j) {
            drawAllTabs(gp4Data.beats[j]);
        }
        
        nextStaff = true;
    }
}

void GP4Renderer::drawAllTabs(const std::vector<std::vector<Beat>>& beats) {
    if (nextStaff) {
        drawNextStaff();
        nextStaff = false;
    }
    
//    for (int i = 0; i < beats.size(); ++i) {
//        drawNextMeasure(beats[i]);
//    }
    
//    std::cout << "tracks count: " << beats.size() << std::endl;
    drawNextMeasure(beats[1]);
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
}

void GP4Renderer::drawNextBeat(const Beat& beat) {
//    std::cout << "drawing beat" << std::endl;
    
    currentBeatX += CHORD_MARGIN;

    currentNoteY = firstLine + TABS_VERTICAL_PADDING;
//    drawNote(beat.notes[3]);
    if (beat.chord.firstStr) {
//        std::cout << "note 1" << std::endl;
//        std::cout << (int) beat.notes[5].fretNumber << std::endl;
        drawNote(beat.notes[5]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING + TABS_VERTICAL_PADDING;
    if (beat.chord.secondStr) {
//        std::cout << "note 2" << std::endl;
//        std::cout << (int) beat.notes[4].fretNumber << std::endl;
        drawNote(beat.notes[4]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING + TABS_VERTICAL_PADDING;
    if (beat.chord.thirdStr) {
//        std::cout << "note 3" << std::endl;
//        std::cout << (int) beat.notes[3].fretNumber << std::endl;
        drawNote(beat.notes[3]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING + TABS_VERTICAL_PADDING;
    if (beat.chord.fourthStr) {
//        std::cout << "note 4" << std::endl;
//        std::cout << (int) beat.notes[2].fretNumber << std::endl;
        drawNote(beat.notes[2]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING + TABS_VERTICAL_PADDING;
    if (beat.chord.fifthStr) {
//        std::cout << "note 5" << std::endl;
//        std::cout << (int) beat.notes[1].fretNumber << std::endl;
        drawNote(beat.notes[1]);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING + TABS_VERTICAL_PADDING;
    if (beat.chord.sixthStr) {
//        std::cout << "note 6" << std::endl;
//        std::cout << (int) beat.notes[0].fretNumber << std::endl;
        drawNote(beat.notes[0]);
    }
}

void GP4Renderer::drawNote(const Note& note) {
//    std::cout << "drawing note" << std::endl;
    char c[2];
    snprintf(c, sizeof(c) / sizeof(char), "%d", note.fretNumber);
    
    std::string fret = c;
    
    
    SDL_Color color {0, 0, 0, 255};
    
    textRenderer.renderText(fret, currentBeatX, currentNoteY, 12, color);
}
