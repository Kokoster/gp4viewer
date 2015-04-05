#pragma once

#include <fstream>
#include <vector>

struct Point {
    int timePosition;
    int verticalPosition;
    char vibrato;
};

struct Bend {
    char type;
    int value;
    int pointsCount;
    std::vector<Point> points;
};

template<typename T>
T readData(std::ifstream& inputStream)  {
    T t;
    inputStream.read(reinterpret_cast<char*>(&t), sizeof(t));
    return t;
}

std::string readString(std::ifstream& inputStream);
std::string readDataBlock(std::ifstream& inputStream, int stringsCount);

Bend readBend(std::ifstream& inputStream);
void printBend(const Bend& bend);