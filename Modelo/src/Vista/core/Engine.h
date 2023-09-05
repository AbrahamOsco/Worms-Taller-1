//
// Created by abraham on 31/08/23.
//

#ifndef MODELO_ENGINE_H
#define MODELO_ENGINE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../Graphics/TextManager.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 750


class Engine {
 private:
    bool running;
    SDL_Window* unWindow;
    SDL_Renderer* unRender;
    TextManager& textManager;

public:
    SDL_Renderer *getUnRender() const;

public:
    Engine(TextManager &textManager);

    bool isRunning();

    void update();

    void events();

    void render();

    void clean();

    ~Engine() = default;

};


#endif //MODELO_ENGINE_H
