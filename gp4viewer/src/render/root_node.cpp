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
#include "note_node.h"

#include <iostream>


RootNode::RootNode(Renderer* renderer, Window* window) {
    this->window = window;
    this->renderer = renderer;
    
    Point position(0, 0);
    setPosition(position);
    
    currentIndex = 0;
    hasMeasure = true;
}

void RootNode::createStaff(Node** rowNoteStaffPtr, Node** rowTabStaffPtr, int* verticalPadding) {
    
    std::unique_ptr<Node> staffNode(new Node());
    
//    std::cout << "padding: " << *verticalPadding << std::endl;
    
    std::unique_ptr<Node> noteStaffNode(new NoteStaffNode(*window, *verticalPadding));
    *rowNoteStaffPtr = noteStaffNode.get();
    setClueNode(*rowNoteStaffPtr);
    staffNode->addChild(noteStaffNode);
    
    *verticalPadding += NOTE_STAFF_LINE_VERTICAL_PADDING * 4 + GENERAL_STAFF_PADDING;
    
//    std::cout << "tab padding: " << *verticalPadding << std::endl;
    
    std::unique_ptr<Node> tabStaffNode(new TabStaffNode(*window, *verticalPadding));
    *rowTabStaffPtr = tabStaffNode.get();
    setTabNode(*rowTabStaffPtr);
    staffNode->addChild(tabStaffNode);
    addChild(staffNode);

}

void RootNode::calculateEverything(const GP4Data& gp4Data) {
    int verticalPadding = 50;
    
    Node* rowNoteStaffPtr;
    Node* rowTabStaffPtr;
    
    createStaff(&rowNoteStaffPtr, &rowTabStaffPtr, &verticalPadding);
    
//    int tabCurrentX = rowTabStaffPtr->getPadding().size.w;
    int currentX = rowNoteStaffPtr->getPadding().size.w;
    
//    while (currentIndex < 13) {
    while (currentIndex < gp4Data.beats.size()) {
        Point currentPosition(currentX, 0);
        
        std::unique_ptr<Node> tabMeasureNode(new MeasureNode());
        tabMeasureNode->setPosition(currentPosition);
        
        std::unique_ptr<Node> noteMeasureNode(new MeasureNode());
        noteMeasureNode->setPosition(currentPosition);
        
        setMeasureNode(rowTabStaffPtr, rowNoteStaffPtr, tabMeasureNode, noteMeasureNode, gp4Data);
        
//        setTabMeasureNode(rowNoteStaffPtr, noteMeasureNode, gp4Data, 0);
        
        currentIndex++;
        
        if (tabMeasureNode->getPosition().x + tabMeasureNode->getPadding().size.w > window->getWidth() - STAFF_LINE_HORIZONTAL_PADDING) {

            verticalPadding += TAB_STAFF_LINE_VERTICAL_PADDING * 5 + STAFF_PADDING_KOEF * GENERAL_STAFF_PADDING;
            
            createStaff(&rowNoteStaffPtr, &rowTabStaffPtr, &verticalPadding);
            
            currentX = rowNoteStaffPtr->getPadding().size.w;
            currentPosition.x = currentX;
            currentPosition.x = currentX;
            
            tabMeasureNode->setPosition(currentPosition);
            noteMeasureNode->setPosition(currentPosition);
        }
        
        currentX += tabMeasureNode->getPadding().size.w;
        rowTabStaffPtr->addChild(tabMeasureNode);
        rowNoteStaffPtr->addChild(noteMeasureNode);
    }
}

void RootNode::setMeasureNode(Node* rowTabStaffPtr, Node* rowNoteStaffPtr, std::unique_ptr<Node>& tabMeasureNode, std::unique_ptr<Node>& noteMeasureNode, const GP4Data& gp4Data) {
    setNoteMeasureNode(rowNoteStaffPtr, noteMeasureNode, gp4Data);

    setTabMeasureNode(rowTabStaffPtr, tabMeasureNode, gp4Data);
    
//    std::cout << "note: " << noteMeasureNode->getPadding().size.w << std::endl;
//    std::cout << "tab:" << tabMeasureNode->getPadding().size.w << std::endl;
    
    int padding = std::max(noteMeasureNode->getPadding().size.w, tabMeasureNode->getPadding().size.w);
    
    if (tabMeasureNode->getPadding().size.w < padding) {
        padding -= tabMeasureNode->getPadding().size.w;
        tabMeasureNode->setPadding(padding);
    }
    else if (noteMeasureNode->getPadding().size.w < padding) {
        padding -= noteMeasureNode->getPadding().size.w;
        noteMeasureNode->setPadding(padding);
    }
}

void RootNode::setNoteMeasureNode(Node* rowStaff, std::unique_ptr<Node>& measureNode, const GP4Data& gp4Data) {
    const std::vector<Beat> beats = gp4Data.beats[currentIndex][2];
    
//    int currentX = rowStaff->getPadding().size.w + CHORD_MARGIN;
    int currentX = CHORD_MARGIN; // отступ в начале такта
    
    for (auto& beat : beats) {
        std::unique_ptr<Node> beatNode(new BeatNode());
        Point position(currentX, 0);
        beatNode->setPosition(position);
        
        setNoteBeatNode(beatNode, beat);
        Node* rowBeatPtr = beatNode.get();
        
        measureNode->addChild(beatNode);
        currentX += rowBeatPtr->getPadding().size.w;
    }
}

void RootNode::setTabMeasureNode(Node* rowStaff, std::unique_ptr<Node>& measureNode, const GP4Data& gp4Data) {
    const std::vector<Beat> beats = gp4Data.beats[currentIndex][2];
    
    //    int currentX = rowStaff->getPadding().size.w + CHORD_MARGIN;
    int currentX = CHORD_MARGIN; // отступ в начале такта
    
    for (auto& beat : beats) {
        std::unique_ptr<Node> beatNode(new BeatNode());
        Point position(currentX, 0);
        beatNode->setPosition(position);
        
        setTabBeatNode(beatNode, beat);
        Node* rowBeatPtr = beatNode.get();
        
        measureNode->addChild(beatNode);
        currentX += rowBeatPtr->getPadding().size.w;
    }
}

std::string getString(const Note& note) {
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

std::string getNoteType(const Note& note, int line) {
    if ((int) note.type < 2) {
        if (line == -5 || line == -3  || line == -1 ||
            line == 11 || line == 13 || line == 15 ||
            line == 17 || line == 19)
        {
            return "Cwhole_note.png";
        }
        
        return "whole_note.png";
    }

    return "";
}

NoteStruct findNote(const Note& note, int stringNumber) {
    int firstNote = 0;
    int octave = 0;
    
    switch (stringNumber) {
        case 1: firstNote = MI;
            octave = SECOND;
            break;
        case 2: firstNote = SI;
            octave = FIRST;
            break;
        case 3: firstNote = SOL;
            octave = FIRST;
            break;
        case 4: firstNote = RE;
            octave = FIRST;
            break;
        case 5: firstNote = LA;
            octave = SMALL;
            break;
        case 6: firstNote = MI;
            octave = SMALL;
            break;
    }
    
    NoteStruct foundNote;
    
    foundNote.note = (firstNote + note.fretNumber) % 12;
    
    if (foundNote.note == DO_SHARP || foundNote.note == RE_SHARP  ||
        foundNote.note == FA_SHARP || foundNote.note == SOL_SHARP ||
        foundNote.note == LA_SHARP) {
        foundNote.note--;
        foundNote.sharp = true;
    }
    else {
        foundNote.sharp = false;
    }
        
    foundNote.octave = octave;
    
    if ((firstNote + note.fretNumber) / 12 > 0) {
        foundNote.octave++;
    }
    
    return foundNote;
}

int findLine(NoteStruct& noteStruct) {
    int line = 0;
    
    switch (noteStruct.note) {
        case DO:  line = -1;
                  break;
        case RE:  line = 0;
                  break;
        case MI:  line = 1;
                  break;
        case FA:  line = 2;
                  break;
        case SOL: line = 3;
                  break;
        case LA:  line = 4;
                  break;
        case SI:  line = 5;
                  break;
    }
    
    switch (noteStruct.octave) {
        case SMALL:  line -= 7;
                     break;
        case SECOND: line += 7;
                     break;
        case THIRD:  line += 2 * 7;
        default:     break;
    }
    
    return line;
}


Point findNotePosition(const Note& note, int stringNumber, int* line) {
    NoteStruct foundNote = findNote(note, stringNumber);
    *line = findLine(foundNote);
    int initialY = 4 * NOTE_STAFF_LINE_VERTICAL_PADDING;
    
    int padding = NOTE_STAFF_LINE_VERTICAL_PADDING / 2;
    int y = initialY - *line * padding;
    
    Point position(0, y);
    return position;
}

void RootNode::setNoteBeatNode(std::unique_ptr<Node>& beatNode, const Beat& beat)
{
    Point position;
    int line;
    
//    std::cout << (int) beat.notes[2].type << std::endl;
    
    if (beat.chord.firstStr) {
        position = findNotePosition(beat.notes[5], 1, &line);
        std::string type = getNoteType(beat.notes[5], line);
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.secondStr) {
        position = findNotePosition(beat.notes[4], 2, &line);
        std::string type = getNoteType(beat.notes[4], line);
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.thirdStr) {
        position = findNotePosition(beat.notes[3], 3, &line);
        std::string type = getNoteType(beat.notes[3], line);
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.fourthStr) {
        position = findNotePosition(beat.notes[2], 4, &line);
        std::string type = getNoteType(beat.notes[2], line);
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.fifthStr)  {
        position = findNotePosition(beat.notes[1], 5, &line);
        std::string type = getNoteType(beat.notes[1], line);
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.sixthStr) {
//        std::cout << (int) beat.notes[0].fretNumber << std::endl;
        
        position = findNotePosition(beat.notes[0], 6, &line);
        std::string type = getNoteType(beat.notes[0], line);
//        std::cout << "type: " << type << std::endl;
        
        std::unique_ptr<Node> noteNode(new NoteNode(*renderer, type));
        noteNode->setPosition(position);
//        std::cout << noteNode->getGlobalPosition().x << " " << noteNode->getGlobalPosition().y << std::endl;
        beatNode->addChild(noteNode);
    }
}

void RootNode::setTabBeatNode(std::unique_ptr<Node>& beatNode, const Beat& beat) {
    
    if (beat.chord.firstStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[5]), FONT_SIZE));
        Point position(0, -1 * TAB_STAFF_LINE_VERTICAL_PADDING / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.secondStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[4]), FONT_SIZE));
        Point position(0, TAB_STAFF_LINE_VERTICAL_PADDING / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.thirdStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[3]), FONT_SIZE));
        Point position(0, TAB_STAFF_LINE_VERTICAL_PADDING * 3 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.fourthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[2]), FONT_SIZE));
        Point position(0, TAB_STAFF_LINE_VERTICAL_PADDING * 5 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.fifthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[1]), FONT_SIZE));
        Point position(0, TAB_STAFF_LINE_VERTICAL_PADDING * 7 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
    
    if (beat.chord.sixthStr) {
        std::unique_ptr<Node> noteNode(new TextNode(*renderer, getString(beat.notes[0]), FONT_SIZE));
        Point position(0, TAB_STAFF_LINE_VERTICAL_PADDING * 9 / 2);
        noteNode->setPosition(position);
        beatNode->addChild(noteNode);
    }
}

void RootNode::setTabNode(Node* staffNode) {
    std::unique_ptr<Node> tabNode(new BeatNode());
    Point position(CHORD_MARGIN / 2, 0);
    tabNode->setPosition(position);
    
    std::unique_ptr<Node> tLetter(new TextNode(*renderer, "T", FONT_SIZE));
    Point tPosition(0, TAB_STAFF_LINE_VERTICAL_PADDING);
    tLetter->setPosition(tPosition);
    tabNode->addChild(tLetter);
    
    
    std::unique_ptr<Node> aLetter(new TextNode(*renderer, "A", FONT_SIZE));
    Point aPosition(0, 2 * TAB_STAFF_LINE_VERTICAL_PADDING);
    aLetter->setPosition(aPosition);
    tabNode->addChild(aLetter);
    
    std::unique_ptr<Node> bLetter(new TextNode(*renderer, "B", FONT_SIZE));
    Point bPosition(0, 3 * TAB_STAFF_LINE_VERTICAL_PADDING);
    bLetter->setPosition(bPosition);
    tabNode->addChild(bLetter);
    
    staffNode->addChild(tabNode);
}

void RootNode::setClueNode(Node* staffNode) {
    std::unique_ptr<Node> tabNode(new NoteNode(*renderer, "clue.png"));
    Point position(CHORD_MARGIN / 2, -NOTE_STAFF_LINE_VERTICAL_PADDING);
    tabNode->setPosition(position);
    
    staffNode->addChild(tabNode);
}


