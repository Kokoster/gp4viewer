#pragma once

#include <vector>

#include "note.h"

struct Application {
    bool volume  : 1;
    bool pan     : 1;
    bool chorus  : 1;
    bool reverb  : 1;
    bool phaser  : 1;
    bool tremolo : 1;
    bool _skip   : 2;
};

struct ChangeEvent {
    char instrument;
    char volume;
    char pan;
    char chorus;
    char reverb;
    char phaser;
    char tremolo;
    int  tempo;
    char volumeChangeDuration;
    char panChangeDuration;
    char chorusChangeDuration;
    char reverbChangeDuration;
    char phaserChangeDuration;
    char tremoloChangeDuration;
    char tempoChangeDuration;

    Application application;
};

struct EffectsHeader {
    bool _skip1             : 5;
    bool containsTapPopSlap : 1;
    bool containsStroke     : 1;
    bool _skip2             : 1;
};

struct NewEffects {
    bool containsRageo      : 1;
    bool containsPickStroke : 1;
    bool containsTremolo    : 1;
    bool _skip              : 5;
};

struct BeatEffects {
    EffectsHeader header;
    NewEffects newEffects;
    char tapPopSlap;
    Bend tremolo;
    char upStroke;
    char downStroke;
    bool rageo;
    char pickStroke;
};


struct ChordDiagram {
    char header;
    char sharp;
    // char _skip1[3];
    char root;
    char tonality;
    char chordAdd;
    int bass;
    int dimAug;
    char addedNote;
    std::string chordName;
    // char _skip2[2];
    char fifthTonality;
    char ninthTonality;
    char eleventhTonality;
    int baseFret;
    int frets[7];
    int barresCount; // char
    char barreFrets[5];
    char barreStart[5];
    char barreEnd[5];
    char ommisions[7];
    // char _skip3;
    char fingering[7];
    char showFingering;
};

struct BeatHeader {
    bool containsDottedNotes  : 1;
    bool containsChordDiagram : 1;
    bool containsText         : 1;
    bool containsEffects      : 1;
    bool containsChangeEvent  : 1;
    bool isNTuplet            : 1;
    bool hasStatus            : 1;
    bool _skip                : 1;
};

struct Beat {
    BeatHeader header;
    Tab tab;
    char status;
    char duration;
    int nTuplet;
    char chordsCount; // int
    std::vector<ChordDiagram> chords;
    std::string text;
    BeatEffects effects;
    ChangeEvent changeEvent;
    Note notes[6];
};

Beat readBeat(std::ifstream& inputStream);
void printBeat(const Beat& beat);