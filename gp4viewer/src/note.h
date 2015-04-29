#pragma once

#include "common.h"

struct NoteEffectsHeader1 {
    bool containsBend       : 1;
    bool containsHammerPull : 1;
    bool containsSlideV3    : 1;
    bool letRing            : 1;
    bool containsGraceNote  : 1;
    bool _skip              : 3;
};

struct NoteEffectsHeader2 {
    bool playedStaccato : 1;
    bool palmMute       : 1;
    bool tremoloPicking : 1;
    bool containsSlide  : 1;
    bool harmonics      : 1;
    bool containsTrill  : 1;
    bool handVibrato    : 1;
    bool _skip          : 1;
};

struct GraceNote {
    char fret;
    char dynamic;
    char transition;
    char duration;
};

struct Trill {
    char fret;
    char period;
};

struct NoteEffects {
    NoteEffectsHeader1 header1;
    NoteEffectsHeader2 header2;
    Bend bend;
    GraceNote graceNote;
    char tremolo;
    char slide;
    char harmonics;
    Trill trill;

    bool letRing;
    bool hammerPull;
    bool handVibrato;
    bool palmMute;
    bool isStaccato;
};

struct NoteHeader {
    bool timeIndependentDuration : 1;
    bool dottedNote              : 1;
    bool ghostNote               : 1;
    bool containsEffects         : 1;
    bool hasDynamic              : 1;
    bool containsType            : 1;
    bool isAccentuated           : 1;
    bool fingering               : 1;
};

struct Note {
    NoteHeader header;
    char tabString;
    char type; // CHANGE: short -> char
    char timeDuration;
    char nTuplet;
    char dynamic;
    char fretNumber;
    char leftFingering;
    char rightFingering;
    bool isAccentuated;
    NoteEffects effects;
};

struct Chord {
    bool _skip     : 1;
    bool sixthStr  : 1;
    bool fifthStr  : 1;
    bool fourthStr : 1;
    bool thirdStr  : 1;
    bool secondStr : 1;
    bool firstStr  : 1;
    bool _skip2    : 1;
};

Chord readChord(std::ifstream& inputStream, Note* notes);
void printNote(const Note& note);