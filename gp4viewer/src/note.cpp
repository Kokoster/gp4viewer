#include "note.h"

#include <iostream>
#include <fstream>

GraceNote readGraceNote(std::ifstream& inputStream) {
    GraceNote graceNote = {
        .fret = 0,
        .dynamic = 0,
        .transition = 0,
        .duration = 0
    };

    graceNote.fret       = readData<char>(inputStream);
    graceNote.dynamic    = readData<char>(inputStream);
    graceNote.transition = readData<char>(inputStream);   
    graceNote.duration   = readData<char>(inputStream);

    return graceNote;
}

Trill readTrill(std::ifstream& inputStream) {
    Trill trill = {
        .fret = 0,
        .period = 0
    };

    trill.fret   = readData<char>(inputStream);
    trill.period = readData<char>(inputStream);

    return trill;
}

NoteEffects readNoteEffects(std::ifstream& inputStream) {
    NoteEffects effects = {
        .tremolo = 0,
        .slide = 0,
        .harmonics = 0,
        .letRing = false,
        .hammerPull = false,
        .handVibrato = false,
        .palmMute = false,
        .isStaccato = false
    };

    effects.header1 = readData<NoteEffectsHeader1>(inputStream);
    effects.header2 = readData<NoteEffectsHeader2>(inputStream);

    if (effects.header1.containsBend) {
        effects.bend = readBend(inputStream);
    }

    if (effects.header1.containsGraceNote) {
        effects.graceNote = readGraceNote(inputStream);
    }

    if (effects.header2.tremoloPicking) {
        effects.tremolo = readData<char>(inputStream);
    }

    if (effects.header2.containsSlide) {
        effects.slide = readData<char>(inputStream);
    }

    if (effects.header2.harmonics) {
        effects.harmonics = readData<char>(inputStream);
    }

    if (effects.header2.containsTrill) {
        effects.trill = readTrill(inputStream);
    }

    if (effects.header1.letRing) {
        effects.letRing = true;
    }

    if (effects.header1.containsHammerPull) {
        effects.hammerPull = true;
    }

    if (effects.header2.handVibrato){
        effects.handVibrato = true;
    }

    if (effects.header2.palmMute) {
        effects.palmMute = true;
    }

    if (effects.header2.playedStaccato) {
        effects.isStaccato = true;
    }

    return effects;
}

Note readNote(std::ifstream& inputStream) {
    Note note {
        .type           = 0,
        .timeDuration   = 0,
        .nTuplet        = 0,
        .dynamic        = 0,
        .fretNumber     = 0,
        .leftFingering  = 0,
        .rightFingering = 0,
        .isAccentuated  = false
    };

    note.header = readData<NoteHeader>(inputStream);
    // std::cout << std::hex;
    // std::cout << "note header: " << *reinterpret_cast<int*>(&note.header) << std::endl;
    // std::cout << std::dec;

    if (note.header.containsType) {
        note.type = readData<char>(inputStream);  // CHANGE: short -> char
    }

    if (note.header.timeIndependentDuration) {
        note.timeDuration = readData<char>(inputStream);
        note.nTuplet      = readData<char>(inputStream);
    }

    if (note.header.hasDynamic) {
        note.dynamic = readData<char>(inputStream);
    }

    if (note.header.containsType) {
        note.fretNumber = readData<char>(inputStream);
    }

    if (note.header.fingering) {
        note.leftFingering  = readData<char>(inputStream);
        note.rightFingering = readData<char>(inputStream); 
    }

    if (note.header.isAccentuated) {
        note.isAccentuated = true;
    }

    if (note.header.containsEffects) {
        note.effects = readNoteEffects(inputStream);
    }

    return note;
}

Chord readChord(std::ifstream& inputStream, Note* notes) {
    Chord chord = readData<Chord>(inputStream);
    if (*reinterpret_cast<int*>(&chord) == 0) {
        return chord;
    }
//    std::cout << std::hex;
//    std::cout << "tab: " << *reinterpret_cast<int*>(&tab) << std::endl;
//    std::cout << std::dec;

    if (chord.firstStr) {
        // std::cout << "reading first note" << std::endl;
        notes[5] = readNote(inputStream);
    }

    if (chord.secondStr) {
        // std::cout << "reading second note" << std::endl;
        notes[4] = readNote(inputStream);
    }

    if (chord.thirdStr) {
        // std::cout << "reading third note" << std::endl;
        notes[3] = readNote(inputStream);
    }

    if (chord.fourthStr) {
        // std::cout << "reading fourth note" << std::endl;
        notes[2] = readNote(inputStream);
    }

    if (chord.fifthStr) {
        // std::cout << "reading fifth note" << std::endl;
        notes[1] = readNote(inputStream);
    }

    if (chord.sixthStr) {
        // std::cout << "reading sixth note" << std::endl;
        notes[0] = readNote(inputStream);
    }

    return chord;
}

void printNoteEffects(const NoteEffects& effects) {
    std::cout << "header1 " << std::hex << (int)*reinterpret_cast<const char*>(&effects.header1) << std::endl;
    std::cout << "header2 " << std::hex << (int)*reinterpret_cast<const char*>(&effects.header2) << std::endl;
    std::cout << std::dec;


    if (effects.header1.containsBend) {
        std::cout << "contains bend" << std::endl;
        printBend(effects.bend);
    }
}

void printNote(const Note& note) {
    if (note.header.containsType) {
        std::cout << "type: " << (int)note.type << std::endl;
    }

    if (note.header.timeIndependentDuration) {
        std::cout << "time duration: " << (int)note.timeDuration << std::endl;
        std::cout << "tuplet: " << (int)note.nTuplet << std::endl;
    }

    if (note.header.hasDynamic) {
        std::cout << "dynamic: " << (int)note.dynamic << std::endl;
    }

    if (note.header.containsType) {
        std::cout << "fret number: " << (int)note.fretNumber << std::endl;
    }

    if (note.header.fingering) {
        std::cout << "fingering: " << (int)note.leftFingering << " " << note.rightFingering << std::endl;
    }

    if (note.header.isAccentuated) {
        std::cout << "is Accentuated" << std::endl;
    }

    if (note.header.containsEffects) {
        std::cout << "contains effects" << std::endl;
        printNoteEffects(note.effects);
    }
} 