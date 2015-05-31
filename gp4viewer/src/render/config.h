//
//  congig.h
//  gp4viewer
//
//  Created by Ольга Диденко on 24.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

# pragma once

#define STAFF_LINE_HORIZONTAL_PADDING 20
#define TAB_STAFF_LINE_VERTICAL_PADDING 11
#define NOTE_STAFF_LINE_VERTICAL_PADDING 8
#define STAFF_PADDING_KOEF 2
#define GENERAL_STAFF_PADDING 50
#define CHORD_MARGIN 20
#define FONT_SIZE 11

enum NOTES_ENUM {DO, DO_SHARP, RE, RE_SHARP, MI, FA, FA_SHARP, SOL, SOL_SHARP, LA, LA_SHARP, SI};
enum OCTAVE_ENUM {SMALL, FIRST, SECOND, THIRD};

struct NoteStruct {
    NoteStruct operator=(const NoteStruct& noteSruct);
   
    bool sharp;
    
    int note;
    int octave;
};