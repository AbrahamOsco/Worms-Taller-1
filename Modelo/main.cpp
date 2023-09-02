#include <iostream>

#include <SDL2/SDL.h>
#include "src/core/Engine.h"
#include "src/Graphics/TextManager.h"

#include <stdio.h>

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "SDL fue inicializado con exito\n";
    }
    TextManager textManager;
    Engine unEngine(textManager);
    while (unEngine.isRunning()){
        unEngine.events();
        unEngine.update();
        unEngine.render();
    }
    return 0;
}



