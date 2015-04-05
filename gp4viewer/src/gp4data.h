#pragma once

#include <memory>
#include <vector>
#include <string>

#include "beat.h"

#define PORTS_COUNT 4
#define CNANNELS_COUNT 16

struct Channel {
    int instrument;
    char volume;
    char balance;
    char chorus;
    char reverb;
    char phaser;
    char tremolo;
    char blank1;
    char blank2;
};

struct Port {
    Channel channels[CNANNELS_COUNT];
};

struct Color {
    char white;
    char blue;
    char red;
    char green;
};

struct Marker {
    std::string name;
    Color color;
};

struct MeasureFlags {
    bool containsNumerator : 1;
    bool containsDenominator : 1;
    bool containsBeginningRepeat : 1;
    bool containsEndRepeat : 1;
    bool containsAltenativeEnding : 1;
    bool containsMarker : 1;
    bool containsTonality : 1;
    bool containsDoubleBar : 1;
};

struct Measure { 
    MeasureFlags flag;
    char numerator;
    char denominator;
    bool beginningRepeat;
    char endRepeat;
    char altenativeEnding;
    Marker marker;
    char tonality;
    bool doubleBar;
};

struct TrackHeader {
    bool drum : 1;
    bool tweStringedGuitar : 1;
    bool banjo : 1;
    bool _skip : 5;
};

struct Track {
    TrackHeader header;
    std::string name;
    int stringsCount;
    int tuning[7];
    int port;
    int channel;
    int effectsChannel;
    int fretsCount;
    int capo;
    Color color;
};

struct GP4Data {
    std::string version;
    std::string dataBlock;
    std::string notice;
    char tripletFeel;

    int tempo;
    char key;
    char octave;

    Port ports[PORTS_COUNT];

    int measuresCount;
    std::vector<Measure> measures;

    int tracksCount;
    std::vector<Track> tracks;

    std::vector<std::vector<std::vector<Beat>>> beats;
};