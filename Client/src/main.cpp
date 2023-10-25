#include "SDL2pp/SDL2pp.hh"
#include "core/Engine.h"

int main () {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Engine engine;
    engine.init();
    while (engine.running()) {
        engine.events();
        engine.update();
        engine.render();
        engine.tick();
    }
    return 0;
}