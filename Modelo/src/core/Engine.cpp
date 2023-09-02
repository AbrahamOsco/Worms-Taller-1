#include <iostream>
#include "Engine.h"
#include "../Graphics/TextManager.h"

Engine::Engine(TextManager &textManager) : textManager(textManager) {
    running = true;
    if(SDL_Init(SDL_INIT_VIDEO) != 0 or IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) == 0 ){
        SDL_Log("Error en el constructor del engine %s\n", SDL_GetError() );
    }
    this->unWindow = SDL_CreateWindow("Un Titulo de Ventana",
                                      SDL_WINDOWPOS_CENTERED, 0,
                                      SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if( !unWindow ){
        SDL_Log("Error en el create Window %s\n", SDL_GetError() );
    }

    this->unRender = SDL_CreateRenderer(unWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( !unRender){
        SDL_Log("Error en el create Renderer %s\n", SDL_GetError() );
    }
    textManager.load("imgInicial", "../assets/Worms1.png", unRender);

}

bool Engine::isRunning(){
    return running;
}

void Engine::update(){
}

void Engine::events(){
    SDL_Event unEvent;
    SDL_PollEvent(&unEvent);
    if(unEvent.type == SDL_QUIT){
        SDL_Quit();
    }
}

void Engine::render(){
    SDL_RenderClear(unRender);
    SDL_SetRenderDrawColor(unRender, 124, 120, 200, 4);

    textManager.draw(unRender, "imgInicial", 100, 100, 1090, 606, SDL_FLIP_NONE );
    SDL_RenderPresent(unRender);
}

void Engine::clean(){

}

SDL_Renderer* Engine::getUnRender() const {
    return unRender;
}


