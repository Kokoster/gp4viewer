#include "beat.h"

#include <iostream>
#include <fstream>

ChordDiagram readChordDiagram(std::ifstream& inputStream) {
    ChordDiagram chord = {
        .header           = 0,
        .sharp            = 0,
        .root             = 0,
        .tonality         = 0,
        .chordAdd         = 0,
        .bass             = 0,
        .dimAug           = 0,
        .addedNote        = 0,
        .fifthTonality    = 0,
        .ninthTonality    = 0,
        .eleventhTonality = 0,
        .baseFret         = 0,
        .frets            = {0, 0, 0, 0, 0, 0, 0},
        .barresCount      = 0,
        .barreFrets       = {0, 0, 0, 0, 0},
        .barreStart       = {0, 0, 0, 0, 0},
        .barreEnd         = {0, 0, 0, 0, 0},
        .ommisions        = {0, 0, 0, 0, 0, 0, 0},
        .fingering        = {0, 0, 0, 0, 0, 0, 0},
        .showFingering    = 0
    };

    chord.header = readData<char>(inputStream);
    chord.sharp  = readData<char>(inputStream);

    inputStream.ignore(2);

    chord.root      = readData<char>(inputStream);
    chord.tonality  = readData<char>(inputStream);
    chord.chordAdd  = readData<char>(inputStream);
    chord.bass      = readData<int>(inputStream);
    chord.dimAug    = readData<int>(inputStream);
    chord.addedNote = readData<char>(inputStream);
    chord.chordName = readString(inputStream);

    inputStream.ignore(20 - chord.chordName.size());
    inputStream.ignore(2);

    chord.fifthTonality = readData<char>(inputStream);

    if (chord.chordAdd == 11 || chord.chordAdd == 13) {
        chord.ninthTonality    = readData<char>(inputStream);
    }
    else inputStream.ignore(1);

    if (chord.chordAdd == 13) {
        chord.eleventhTonality = readData<char>(inputStream);
    }
    else inputStream.ignore(1);

    chord.baseFret = readData<int>(inputStream);

    for (int i = 0; i < 7; ++i) {
        chord.frets[i] = readData<int>(inputStream);
    }

    chord.barresCount = readData<int>(inputStream); // char
    for (int i = 0; i < 5; ++i) {
        chord.barreFrets[i] = readData<char>(inputStream);
    }

    for (int i = 0; i < 5; ++i) {
        chord.barreStart[i] = readData<char>(inputStream);
    }

    for (int i = 0; i < 5; ++i) {
        chord.barreEnd[i] = readData<char>(inputStream);
    }

    for (int i = 0; i < 4; ++i) {
        chord.ommisions[i] = readData<char>(inputStream);
    }

    if (chord.chordAdd > 8) {
        chord.ommisions[4] = readData<char>(inputStream);
    }

    if (chord.chordAdd > 10) {
        chord.ommisions[5] = readData<char>(inputStream);
    }

    if (chord.chordAdd > 12) {
        chord.ommisions[6] = readData<char>(inputStream);
    }

    inputStream.ignore(1);

    for (int i = 0; i < 7; ++i) {
        chord.fingering[i] = readData<char>(inputStream);
    }

    chord.showFingering = readData<char>(inputStream);

    return chord;
}

BeatEffects readBeatEffects(std::ifstream& inputStream) {
    BeatEffects effects = {
        .tapPopSlap = 0,
        .upStroke = 0,
        .downStroke = 0,
        .rageo = false,
        .pickStroke = 0
    };

    effects.header = readData<EffectsHeader>(inputStream);
    effects.newEffects = readData<NewEffects>(inputStream);

    if (effects.header.containsTapPopSlap) {
        effects.tapPopSlap = readData<char>(inputStream);
    }

    if (effects.newEffects.containsTremolo) {
        effects.tremolo = readBend(inputStream);
    }

    if (effects.header.containsStroke) {
        effects.upStroke   = readData<char>(inputStream);
        effects.downStroke = readData<char>(inputStream);
    }

    if (effects.newEffects.containsRageo) {
        effects.rageo = true;
    }

    if (effects.newEffects.containsPickStroke) {
        effects.pickStroke = readData<char>(inputStream);
    }

    return effects;
}

ChangeEvent readChangeEvent(std::ifstream& inputStream) {
    ChangeEvent changeEvent {
        .instrument = 0,
        .volume = 0,
        .pan = 0,
        .chorus = 0,
        .reverb = 0,
        .phaser = 0,
        .tremolo = 0,
        .tempo = 0,
        .volumeChangeDuration = 0,
        .panChangeDuration = 0,
        .chorusChangeDuration = 0,
        .reverbChangeDuration = 0,
        .phaserChangeDuration = 0,
        .tremoloChangeDuration = 0,
        .tempoChangeDuration = 0
    };

    changeEvent.instrument            = readData<char>(inputStream);
    // std::cout << "change event instrument : " << (int)changeEvent.instrument << std::endl;
    changeEvent.volume                = readData<char>(inputStream);
    changeEvent.pan                   = readData<char>(inputStream);
    changeEvent.chorus                = readData<char>(inputStream);
    changeEvent.reverb                = readData<char>(inputStream);
    changeEvent.phaser                = readData<char>(inputStream);
    changeEvent.tremolo               = readData<char>(inputStream);
    changeEvent.tempo                 = readData<int>(inputStream);

    if (changeEvent.volume > 0) {
        changeEvent.volumeChangeDuration  = readData<char>(inputStream);
    }

    if (changeEvent.pan > -1) {
        changeEvent.panChangeDuration     = readData<char>(inputStream);        
    }

    if (changeEvent.chorus > -1) {
        changeEvent.chorusChangeDuration  = readData<char>(inputStream);
    }

    if (changeEvent.reverb > -1) {
        changeEvent.reverbChangeDuration  = readData<char>(inputStream);
    }

    if (changeEvent.phaser > -1) {
        changeEvent.phaserChangeDuration  = readData<char>(inputStream);
    }

    if (changeEvent.tremolo > -1) {
        changeEvent.tremoloChangeDuration = readData<char>(inputStream);
    }

    if (changeEvent.tempo > -1) {
        changeEvent.tempoChangeDuration   = readData<char>(inputStream); 
    }

    changeEvent.application = readData<Application>(inputStream);
    // std::cout << std::hex;
    // std::cout << "application: " << *reinterpret_cast<int*>(&changeEvent.application) << std::endl;
    // std::cout << std::dec;

    return changeEvent;
}

Beat readBeat(std::ifstream& inputStream) {
    Beat beat = {
        .status      = 0,
        .duration    = 0,
        .nTuplet     = 0,
        .chordsCount = 0,
    };

    // std::cout << "reading header" << std::endl;
    beat.header = readData<BeatHeader>(inputStream);
    // std::cout << std::hex;
    // std::cout << "beat header: " << *reinterpret_cast<int*>(&beat.header) << std::endl;
    // std::cout << std::dec;

    // std::cout << "reading status" << std::endl;
    if (beat.header.hasStatus) {
        beat.status = readData<char>(inputStream);
    }

//    std::cout << "reading duration" << std::endl;
    beat.duration = readData<char>(inputStream);
//    std::cout << "duration: " << (int)beat.duration << std::endl;

//    std::cout << "reading tuplet" << std::endl;
    if (beat.header.isNTuplet) {
        beat.nTuplet = readData<int>(inputStream);
    }

//    std::cout << "reading chord diagram" << std::endl;
    if (beat.header.containsChordDiagram) {
        beat.chordsCount = readData<char>(inputStream); // int

        for (int i = 0; i < beat.chordsCount; ++i) {
            ChordDiagram chord = readChordDiagram(inputStream);
            beat.chords.push_back(chord);
        }
    }

//    std::cout << "reading text" << std::endl;
    if (beat.header.containsText) {
        beat.text = readDataBlock(inputStream, 1);
    }

    // std::cout << "reading effects" << std::endl;
    if (beat.header.containsEffects) {
        beat.effects = readBeatEffects(inputStream);
    }

    // std::cout << "reading change event" << std::endl;
    if (beat.header.containsChangeEvent) {
        // std::cout << "go to change event" << std::endl;
        beat.changeEvent = readChangeEvent(inputStream);
    }

    // std::cout << "reading chord" << std::endl;
    beat.tab = readChord(inputStream, beat.notes);

    return beat;
}

void printChord(const ChordDiagram& chord) {
    std::cout << "header: "            << (int)chord.header           << std::endl;
    std::cout << "sharp: "             << (int)chord.sharp            << std::endl;
    std::cout << "root: "              << (int)chord.root             << std::endl;
    std::cout << "tonality: "          << (int)chord.tonality         << std::endl;
    std::cout << "chordAdd: "          << (int)chord.chordAdd         << std::endl;
    std::cout << "bass: "              << chord.bass                  << std::endl;
    std::cout << "dimAug: "            << chord.dimAug                << std::endl;
    std::cout << "addedNote: "         << (int)chord.addedNote        << std::endl;
    std::cout << "name: "              << chord.chordName             << std::endl;
    std::cout << "fifth tonality: "    << (int)chord.fifthTonality    << std::endl;
    std::cout << "ninth tonality: "    << (int)chord.ninthTonality    << std::endl;
    std::cout << "eleventh tonality: " << (int)chord.eleventhTonality << std::endl;
    std::cout << "base fret: "         << chord.baseFret              << std::endl;
    std::cout << "barres count: "      << chord.barresCount           << std::endl;
}

void printBeat(const Beat& beat) {
    std::cout << "status: " << (int) beat.status << std::endl;
    std::cout << "duration: " << (int) beat.duration << std::endl;
    std::cout << "tuplet: " << beat.nTuplet << std::endl; 
    std::cout << "chords count: " << beat.chordsCount << std::endl;

    for (int i = 0; i < beat.chordsCount; ++i) {
        std::cout << "chord " << i + 1 << std::endl;
        printChord(beat.chords[i]);
    }

    std::cout << "text: " << beat.text << std::endl;

    // if (beat.header.containsEffects) {
    //     printBeatEffects(beat.effects);
    // }

    std::cout << "note info" << std::endl;

    for (int i = 0; i < 6; ++i) {
        std::cout << "note " << i + 1 << ": " << std::endl;
        printNote(beat.notes[i]);
        std::cout << std::endl;
    }
}