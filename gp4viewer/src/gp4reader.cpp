#include "gp4reader.h"

#include <iostream>
#include <fstream>

std::string readNotice(std::ifstream& inputStream) { 
    int stringsCount = readData<int>(inputStream);    
    return readDataBlock(inputStream, stringsCount);
}

void readLyrics(std::ifstream& inputStream) { 
    int trackNumber = readData<int>(inputStream);
//    std::cout << "track number: " << trackNumber << std::endl;

    for (int i = 0; i < 5; ++i) {
        int size = readData<int>(inputStream);

        if (size == 1) {
            inputStream.ignore(4);
        }
    }
}

// void setKeys(int key, char* signature) {  
//     switch (key) {
//         case -1:
//             signature[6] = -1;
//             break;

//         case -2:
//             signature[2] = -1;
//             signature[6] = -1;
//             break;

//         case -3:
//             signature[2] = -1;
//             signature[5] = -1;
//             signature[6] = -1;
//             break;

//         case -4:
//             signature[1] = -1;
//             signature[2] = -1;
//             signature[5] = -1;
//             signature[6] = -1;
//             break;

//         case -5:
//             signature[1] = -1;
//             signature[2] = -1;
//             signature[4] = -1;
//             signature[5] = -1;
//             signature[6] = -1;
//             break;

//         case -6:
//             signature[0] = -1;
//             signature[1] = -1;
//             signature[2] = -1;
//             signature[4] = -1;
//             signature[5] = -1;
//             signature[6] = -1;
//             break;

//         case -7:
//             signature[0] = -1;
//             signature[1] = -1;
//             signature[2] = -1;
//             signature[3] = -1;
//             signature[4] = -1;
//             signature[5] = -1;
//             signature[6] = -1;
//             break;

//         case 1:
//             signature[3] = 1;
//             break;

//         case 2:
//             signature[0] = 1;
//             signature[3] = 1;
//             break;

//         case 3:
//             signature[0] = 1;
//             signature[3] = 1;
//             signature[4] = 1;
//             break;

//         case 4:
//             signature[0] = 1;
//             signature[1] = 1;
//             signature[3] = 1;
//             signature[4] = 1;
//             break;

//         case 5:
//             signature[0] = 1;
//             signature[1] = 1;
//             signature[3] = 1;
//             signature[4] = 1;
//             signature[5] = 1;
//             break;

//         case 6:
//             signature[0] = 1;
//             signature[1] = 1;
//             signature[2] = 1;
//             signature[3] = 1;
//             signature[4] = 1;
//             signature[5] = 1;
//             break;

//         case 7:
//             signature[0] = 1;
//             signature[1] = 1;
//             signature[2] = 1;
//             signature[3] = 1;
//             signature[4] = 1;
//             signature[5] = 1;
//             signature[6] = 1;
//             break;
//     }
// }

// void printKeys(char* signature) {  
//     char notes[7] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

//     for (int i = 0; i < 7; ++i) {
//         std::cout << notes[i] << ": " << (int) signature[i] << std::endl;
//     }
// }

Channel readChannel(std::ifstream& inputStream) { 
    Channel channel;
    
    channel.instrument = readData<int>(inputStream);     
    channel.volume     = readData<char>(inputStream);
    channel.balance    = readData<char>(inputStream);
    channel.chorus     = readData<char>(inputStream);
    channel.reverb     = readData<char>(inputStream);
    channel.phaser     = readData<char>(inputStream);
    channel.tremolo    = readData<char>(inputStream);
    channel.blank1     = readData<char>(inputStream);
    channel.blank2     = readData<char>(inputStream);

    return channel;
}

void printPorts(Port* ports) {
    for (int i = 0; i < 4; ++i) {
        std::cout << "Port " << i + 1 << std::endl;

        for (int j = 0; j < 16; ++j) {
            std::cout << "Channel " << j + 1 << std::endl;

            std::cout << "instrument: " << ports[i].channels[j].instrument << std::endl;
            std::cout << "volume: " << (int) ports[i].channels[j].volume << std::endl;
            std::cout << "balance: " << (int) ports[i].channels[j].balance << std::endl;
            std::cout << "chorus: " << (int) ports[i].channels[j].chorus << std::endl;
            std::cout << "reverb: " << (int) ports[i].channels[j].reverb << std::endl;
            std::cout << "phaser: " << (int) ports[i].channels[j].phaser << std::endl;
            std::cout << "tremolo: " << (int) ports[i].channels[j].tremolo << std::endl;
            std::cout << "blank1: " << (int) ports[i].channels[j].blank1 << std::endl;
            std::cout << "blank2: " << (int) ports[i].channels[j].blank2 << std::endl;

            std::cout << std::endl;
        }
    }
}

Color readColor(std::ifstream& inputStream) {
    Color color;

    color.red = readData<char>(inputStream);
    color.green = readData<char>(inputStream);
    color.blue = readData<char>(inputStream);
    color.white = readData<char>(inputStream);

    return color;
}

Marker readMarker(std::ifstream& inputStream) {
    Marker marker;

    int size = readData<int>(inputStream);
    marker.name = readString(inputStream);

    marker.color = readColor(inputStream);
    return marker;
}

Measure readMeasure(std::ifstream& inputStream) { 
    Measure measure;

    measure.numerator = 0;
    measure.denominator = 0;
    measure.beginningRepeat = false;
    measure.endRepeat = 0;
    measure.altenativeEnding = 0;
    measure.tonality = 0;
    measure.doubleBar = 0;

    MeasureFlags measureFlags = readData<MeasureFlags>(inputStream);
    measure.flag = measureFlags;

    if (measureFlags.containsNumerator) {
        measure.numerator = readData<char>(inputStream);
    }

    if (measureFlags.containsDenominator) {
        measure.denominator = readData<char>(inputStream);   
    }

    if (measureFlags.containsBeginningRepeat) {
        measure.beginningRepeat = true;
    }

    if (measureFlags.containsEndRepeat) {
        measure.endRepeat = readData<char>(inputStream);
    }

    if (measureFlags.containsAltenativeEnding) {
        measure.altenativeEnding = readData<char>(inputStream);
    }
    
    if (measureFlags.containsMarker) {
        measure.marker = readMarker(inputStream);
    }

    if (measureFlags.containsTonality) {
        measure.tonality = readData<char>(inputStream);
    }

    if (measureFlags.containsDoubleBar) {
        measure.doubleBar = true;
    }

    return measure;
}

void printMeasures(const Measure& measure) {
    std::cout << std::hex;
    std::cout << "flag: "            << *reinterpret_cast<const int*>(&measure.flag) << std::endl;
    std::cout << std::dec;
    std::cout << "numerator "        << (int) measure.numerator              << std::endl;
    std::cout << "denominator "      << (int) measure.denominator            << std::endl;
    std::cout << "beginningRepeat "  << (int) measure.beginningRepeat        << std::endl;
    std::cout << "endRepeat "        << (int) measure.endRepeat              << std::endl;
    std::cout << "altenativeEnding " << (int) measure.altenativeEnding       << std::endl;
    std::cout << "tonality "         << (int) measure.tonality               << std::endl;
    std::cout << "doubleBar "        << (int) measure.doubleBar              << std::endl;
}


Track readTrack(std::ifstream& inputStream) {
    Track track;

    track.name           = "";
    track.stringsCount   = 0;
    track.port           = 0;
    track.channel        = 0;
    track.effectsChannel = 0;
    track.fretsCount     = 0;
    track.capo           = 0;

    track.header = readData<TrackHeader>(inputStream);

    track.name         = readString(inputStream);
    inputStream.ignore(40 - track.name.size());
    track.stringsCount = readData<int>(inputStream);

    for (int i = 0; i < track.stringsCount; ++i) {
        track.tuning[i] = readData<int>(inputStream);
    }
    inputStream.ignore((7 - track.stringsCount) * sizeof(int));

    track.port           = readData<int>(inputStream);
    track.channel        = readData<int>(inputStream);
    track.effectsChannel = readData<int>(inputStream);
    track.fretsCount     = readData<int>(inputStream);
    track.capo           = readData<int>(inputStream);
    track.color          = readColor(inputStream);

    return track;
}

void printTrack(const Track& track) {
    std::cout << "name " << track.name << std::endl;
    std::cout << "stringsCount " << track.stringsCount << std::endl;
    std::cout << "port " << track.port << std::endl;
    std::cout << "channel " << track.channel << std::endl;
    std::cout << "effectsChannel " << track.effectsChannel << std::endl;
    std::cout << "fretsCount " << track.fretsCount << std::endl;
    std::cout << "capo " << track.capo << std::endl;
}

GP4Data readGP4Data(std::ifstream& inputStream) {
    GP4Data gp4Data;  

    gp4Data.version = readString(inputStream);
//    std::cout << gp4Data.version << std::endl;
//    std::cout << std::endl;

    inputStream.ignore(30 - gp4Data.version.size());

    gp4Data.dataBlock = readDataBlock(inputStream, 8);

//    std::cout << std::endl << "notice: " << std::endl;
    gp4Data.notice = readNotice(inputStream);
//    std::cout << gp4Data.notice << std::endl;

    gp4Data.tripletFeel = readData<char>(inputStream);
//    std::cout << "triplet feel: " << gp4Data.tripletFeel << std::endl;

    readLyrics(inputStream);

    gp4Data.tempo = readData<int>(inputStream);
//    std::cout << "tempo: " << gp4Data.tempo << std::endl;

    gp4Data.key = readData<char>(inputStream);
//    std::cout << std::endl << "key " << (int) gp4Data.key << std::endl;

    gp4Data.octave = readData<char>(inputStream);
//    std::cout << "octave: " << (int) gp4Data.octave << std::endl;
    inputStream.ignore(3);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 16; ++j) {
            gp4Data.ports[i].channels[j] = readChannel(inputStream);
        }
    }

    std::cout << std::endl;
    // printPorts(gp4Data.ports);

    gp4Data.measuresCount = readData<int>(inputStream);
//    std::cout << "measures count:" << gp4Data.measuresCount << std::endl;

    gp4Data.tracksCount = readData<int>(inputStream);
//    std::cout << "tracks count:" << gp4Data.tracksCount << std::endl;
//    std::cout << std::endl;

    // gp4Data.measures.resize(gp4Data.measuresCount);
    for (int i = 0; i < gp4Data.measuresCount; ++i) {
        Measure measure = readMeasure(inputStream);
        gp4Data.measures.push_back(measure);
    }

    // for (int i = 0; i < gp4Data.measuresCount; ++i) {
    //     std::cout << "measure: " << i + 1 << std::endl;
    //     printMeasures(gp4Data.measures[i]);
    //     std::cout << std::endl;
    // }

    inputStream.ignore(1);
    // TODO: ignore

    for (int i = 0; i < gp4Data.tracksCount; ++i) {
        Track track = readTrack(inputStream);
        gp4Data.tracks.push_back(track);
    }

    // for (int i = 0; i < gp4Data.tracksCount; ++i) {
    //     std::cout << "track: " << i + 1 << std::endl;
    //     printTrack(gp4Data.tracks[i]);
    //     std::cout << std::endl;
    // }

    for (int i = 0; i < gp4Data.measuresCount; ++i) {
//        std::cout << "i: " << i << std::endl;

        std::vector<std::vector<Beat>> trackBeats;
        for (int j = 0; j < gp4Data.tracksCount; ++j) {
//            std::cout << "j: " << j << std::endl;
            int beatsCount = readData<int>(inputStream);
//            std::cout << "beats count " << beatsCount << std::endl;

            std::vector<Beat> beats;
            for (int k = 0; k < beatsCount; ++k) {
//                std::cout << "k: " << k << std::endl;
                Beat beat = readBeat(inputStream);
//                printBeat(beat);
                beats.push_back(beat);
            }
            trackBeats.push_back(beats);
        }

        gp4Data.beats.push_back(trackBeats);
    }

    return gp4Data;
}
