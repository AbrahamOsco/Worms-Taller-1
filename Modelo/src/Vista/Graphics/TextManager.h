//
// Created by abraham on 01/09/23.
//

#ifndef MODELO_TEXTMANAGER_H
#define MODELO_TEXTMANAGER_H


#include <string>
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <map>

class TextManager {
private:
    std::map<std::string, SDL_Texture*> mapTexturas;

 public:
    TextManager();

    bool load(std::string id, std::string filename, SDL_Renderer* unRender);

    void draw(SDL_Renderer* unRender, std::string id, int x, int y, int width, int height, SDL_RendererFlip flip);

    void drop(std::string id);

    void clean();

};


#endif //MODELO_TEXTMANAGER_H
