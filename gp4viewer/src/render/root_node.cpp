//
//  rootNode.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "root_node.h"

#include "staff_node.h"
#include "measure_node.h"
#include "beat_node.h"
#include "text_node.h"

#include <iostream>


RootNode::RootNode(Renderer* renderer, Window* window) {
    this->window = window;
    this->renderer = renderer;
    
    Point position(0, 0);
    setPosition(position);
    
    currentIndex = 0;
    hasMeasure = true;
}

void RootNode::calculateEverything(const GP4Data& gp4Data) {
    int verticalPadding = STAFF_LINE_VERTICAL_PADDING * STAFF_PADDING_KOEF;
    
    Node* rowStaffPtr;
    std::unique_ptr<Node> staffNode(new StaffNode(*window, verticalPadding));
    rowStaffPtr = staffNode.get();
    setTabNode(rowStaffPtr);
    addChild(staffNode);
    
    int currentX = rowStaffPtr->getPadding().size.w;
//    int currentX = CHORD_MARGIN / 2; // "TAB" position
    
    while (currentIndex < gp4Data.beats.size()) {
        std::unique_ptr<Node> measureNode(new MeasureNode());
        Point position(currentX, 0);
        measureNode->setPosition(position);
        
        setMeasureNode(rowStaffPtr, measureNode, gp4Data);
        currentIndex++;
        
        if (measureNode->getPosition().x + measureNode->getPadding().size.w > window->getWidth() - STAFF_LINE_HORIZONTAL_PADDING) {

            verticalPadding += STAFF_LINE_VERTICAL_PADDING * (STAFF_PADDING_KOEF + 5);
            
            std::unique_ptr<Node> staffNode(new StaffNode(*window, verticalPadding));
            rowStaffPtr = staffNode.get();
            addChild(staffNode); // add next staff
            
            setTabNode(rowStaffPtr);
            currentX = rowStaffPtr->getPadding().size.w;
            
            position.x = currentX;
            measureNode->setPosition(position);
        }
        
        currentX += measureNode->getPadding().size.w;
        rowStaffPtr->addChild(measureNode);
    }
}

void RootNode::setMeasureNode(Node* rowStaff, std::unique_ptr<Node>& measureNode, const GP4Data& gp4Data) {
    const std::vector<Beat> beats = gp4Data.beats[currentIndex][2];
    
//    int currentX = rowStaff->getPadding().size.w + CHORD_MARGIN;
    int currentX = CHORD_MARGIN; // отступ в начале такта
    
    for (auto& beat : beats) {
        std::unique_ptr<Node> beatNode(new BeatNode());
        Point position(currentX, 0);
        beatNode->setPosition(position);
        
        setNoteNode(beatNode, beat);
        currentX += beatNode->getPadding().size.w;
        
        measureNode->addChild(beatNode);
    }
}

std::string getString(Note& note) {
    if ((int) note.type == 3) {
        // dead note
        std::string fret = "X";
        return fret;
    }
    
    if ((int) note.type == 2) {
        // tie note
        return "";
    }
    
    char c[4];
    snprintf(c, 2, "%d", note.fretNumber);
    std::string fret = c;
    
    if (note.header.ghostNote) {
        fret.insert(fret.begin(), '(');
        fret.insert(fret.end(), ')');
    };
    
    return fret;
}

void RootNode::setNoteNode(std::unique_ptr<Node>& beatNode, Beat beat) {
    int currentNoteY = 0;
    
    if (beat.chord.firstStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[5]), FONT_SIZE));
        Point position(0, -1 * STAFF_LINE_VERTICAL_PADDING / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.secondStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[4]), FONT_SIZE));
        Point position(0, STAFF_LINE_VERTICAL_PADDING / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.thirdStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[3]), FONT_SIZE));
        Point position(0, STAFF_LINE_VERTICAL_PADDING * 3 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.fourthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[2]), FONT_SIZE));
        Point position(0, STAFF_LINE_VERTICAL_PADDING * 5 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.fifthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[1]), FONT_SIZE));
        Point position(0, STAFF_LINE_VERTICAL_PADDING * 7 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    currentNoteY += STAFF_LINE_VERTICAL_PADDING;
    if (beat.chord.sixthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[0]), FONT_SIZE));
        Point position(0, STAFF_LINE_VERTICAL_PADDING * 9 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
}

void RootNode::setTabNode(Node* staffNode) {
    std::unique_ptr<Node> tabNode(new BeatNode());
    Point position(CHORD_MARGIN / 2, 0);
    tabNode->setPosition(position);
    
    std::unique_ptr<Node> tLetter(new TextNode(*renderer, "T", FONT_SIZE));
    Point tPosition(0, STAFF_LINE_VERTICAL_PADDING);
    tLetter->setPosition(tPosition);
    tabNode->addChild(tLetter);
    
    
    std::unique_ptr<Node> aLetter(new TextNode(*renderer, "A", FONT_SIZE));
    Point aPosition(0, 2 * STAFF_LINE_VERTICAL_PADDING);
    aLetter->setPosition(aPosition);
    tabNode->addChild(aLetter);
    
    std::unique_ptr<Node> bLetter(new TextNode(*renderer, "B", FONT_SIZE));
    Point bPosition(0, 3 * STAFF_LINE_VERTICAL_PADDING);
    bLetter->setPosition(bPosition);
    tabNode->addChild(bLetter);
    
    staffNode->addChild(tabNode);
}


