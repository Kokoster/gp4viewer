#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#include "SDL.h"
#include "Window.h"
#include "Renderer.h"

#include "gp4data.h"
#include "gp4reader.h"

int main(int argc, char const *argv[])
{
    SDL sdl;
    Window window;
    Renderer renderer(window);
    
    if (argc < 2) {
        std::cout << "Usage: dp4viewer <filename>" << std::endl;
        return -1;
    }

//     std::ifstream inputStream("renbourn_john-the_moon_shines_bright.gp4", std::ios::binary);
//     std::ifstream inputStream("Linkin_Park-Somewhere_I_Belong.gp4", std::ios::binary);
//     std::ifstream inputStream("Bon Jovi - It's my life.gp4", std::ios::binary);
//     std::ifstream inputStream("green_day-boulevard_of_broken_dreams_2.gp4", std::ios::binary);

    std::ifstream inputStream(argv[1], std::ios::binary);
    
    if (inputStream.fail()) {
        std::cout << "fail" << std::endl;
    }

    GP4Data gp4Data = readGP4Data(inputStream);

//     gp4Render(gp4Data);

    return 0;
}