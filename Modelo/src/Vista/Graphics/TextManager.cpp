//
// Created by abraham on 01/09/23.
//

#include "TextManager.h"

TextManager::TextManager() {

}

bool TextManager::load(std::string id, std::string filename, SDL_Renderer* unRender) {
    SDL_Surface* surface = IMG_Load( filename.c_str());
    if (!surface){
        SDL_Log("Error en el surface del load %s\n", SDL_GetError() );
        return false;
    }
    SDL_Texture* unaTextura = SDL_CreateTextureFromSurface(unRender, surface);
    if(!unaTextura){
        SDL_Log("Error en el createTextura del load %s\n", SDL_GetError() );
        return false;
    }

    mapTexturas[id] = unaTextura;

    return true;
}

void TextManager::draw(SDL_Renderer* unRender, std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(unRender, mapTexturas[id], &srcRect, &dstRect, 0, nullptr, flip );

}

void TextManager::drop(std::string id) {

}

void TextManager::clean() {

}
