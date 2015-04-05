#include "common.h"

#include <iostream>
#include <fstream>

#include <string>

std::string readString(std::ifstream& inputStream) {
    char n;
    inputStream.read(&n, sizeof(n));

    // std::cout << "n: " << (int) n << std::endl;

    std::unique_ptr<char> buffer(new char[n]);
    inputStream.read(buffer.get(), n);


    return std::string(buffer.get(), n);
}

std::string readDataBlock(std::ifstream& inputStream, int stringsCount) {   
    std::string block;

    for (int i = 0; i < stringsCount; ++i) {
        int size = readData<int>(inputStream);
        // inputStream.read(reinterpret_cast<char*>(&size), sizeof(size));

        // std::cout << "size: " << size << std::endl;

        std::string info = readString(inputStream);
        block += info;
        // std::cout << info << std::endl;
    }

    return block;
}

Point readPoint(std::ifstream& inputStream) {
    Point point = {
        .timePosition = 0,
        .verticalPosition = 0,
        .vibrato = 0
    };

    point.timePosition     = readData<int>(inputStream);
    point.verticalPosition = readData<int>(inputStream);
    point.vibrato          = readData<char>(inputStream);

    return point;
}

Bend readBend(std::ifstream& inputStream) {
    Bend bend = {
        .type = 0,
        .value = 0,
        .pointsCount = 0
    };

    bend.type  = readData<char>(inputStream);
    bend.value = readData<int>(inputStream);
    bend.pointsCount = readData<int>(inputStream);

    for (int i = 0; i < bend.pointsCount; ++i) {
        Point point = readPoint(inputStream);
        bend.points.push_back(point);
    }

    return bend;
}

void printBend(const Bend& bend) {
    std::cout << "type: " << bend.type << std::endl;
    std::cout << "value: " << bend.value << std::endl;
    std::cout << "points count: " << bend.pointsCount << std::endl;
}