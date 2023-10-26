//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_TEXTUREMANAGER_H
#define WORMS_TALLER_1_TEXTUREMANAGER_H

#include "SDL2pp/SDL2pp.hh"
#include <yaml-cpp/yaml.h>

#include <map>
#include <string>
#include <memory>

class TextureManager {
private:
    std::map<std::string, std::unique_ptr<SDL2pp::Texture>> m_textureMap;
public:
    void parseTexture(const std::string& yamlFileName, SDL2pp::Renderer& renderer);
    void load(const std::string& fileName, std::string& id, SDL2pp::Renderer& renderer);
    void draw(const std::string& id, int x, int y, int width, int height, SDL2pp::Renderer& renderer, SDL_RendererFlip flip);
    void drawFrame(const std::string& id, int x, int y, int width, int height, int currentRow, int currentCol, SDL2pp::Renderer& renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
};


#endif //WORMS_TALLER_1_TEXTUREMANAGER_H
