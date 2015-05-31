//
//  config.cpp
//  gp4viewer
//
//  Created by Ольга Диденко on 31.05.15.
//  Copyright (c) 2015 Olga Didenko. All rights reserved.
//

#include "config.h"

NoteStruct NoteStruct::operator=(const NoteStruct& noteStruct) {
    note = noteStruct.note;
    octave = noteStruct.octave;
    sharp = noteStruct.sharp;
    
    return *this;
}
