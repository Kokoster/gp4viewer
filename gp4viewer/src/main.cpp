#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#include "SDL.h"
#include "Window.h"
#include "Renderer.h"
#include "gp4Renderer.h"

#include "gp4data.h"
#include "gp4reader.h"

#include "point.h"
#include "root_node.h"
#include "config.h"

#include "node_test_case.h"


int main(int argc, char const *argv[])
{
    SDL sdl;
    Window window;
    Renderer renderer(window);
    GP4Renderer  gp4Renderer(&renderer, &window);
    
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
    
//    runTests();
//    exit(0);

    GP4Data gp4Data = readGP4Data(inputStream);
    
    RootNode rootNode(&renderer, &window);
    rootNode.calculateEverything(gp4Data);

//    gp4Renderer.renderGP4Data(gp4Data, 0);
//    renderer.present();
    
    while (1) {
        renderer.setColor(255, 255, 255, 255);
        renderer.clear();
        
        SDL_Event e;
        bool exit = false;
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN &&
                e.key.keysym.sym == SDLK_ESCAPE)
            {
                exit = true;
                break;
            }
            
//            if (e.type == SDL_MOUSEBUTTONDOWN) {
//                yFirst = e.button.y;
//                down = true;
//            } else if (e.type == SDL_MOUSEMOTION && down) {
//                currentY = e.motion.y;
//                
//                int yDelta = currentY - yFirst;
//
//                gp4Renderer.renderGP4Data(gp4Data, yDelta);
//                renderer.present();
//            }
//            else if (e.type == SDL_MOUSEBUTTONUP) {
//                down = false;
//            }
//
            if (e.type == SDL_MOUSEWHEEL) {
                int lastPosition = -1 * rootNode.getPadding().size.h;
                
//                currentY = e.wheel.y;
                Point position = rootNode.getPosition();
                position.y += e.wheel.y;
                if (position.y > 0) {
                    position.y = 0;
                }
                else if (position.y < lastPosition) {
                    position.y = lastPosition;
                }
                    
                rootNode.setPosition(position);
                
//                gp4Renderer.renderGP4Data(gp4Data, currentY);
//                renderer.present();
            }
            
        }

        rootNode.render(renderer);
        renderer.present();

        if (exit) break;
    };

    return 0;
}