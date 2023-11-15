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
    void parseTexture(const std::string &yamlFileName, SDL2pp::Renderer &renderer);

    void load(const std::string &fileName, std::string &id, SDL2pp::Renderer &renderer);

    void
    draw(const std::string &id, int x, int y, int width, int height, SDL2pp::Renderer &renderer, SDL_RendererFlip flip);

    void drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentCol,
                   SDL2pp::Renderer &renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void
    drawTextBox(const std::string &text, int x, int y, const std::string &fontPath, int fontSize,
                SDL_Color textColor, SDL_Color boxColor, SDL2pp::Renderer &renderer);

    void drawText(const std::string &text, int x, int y, const std::string &fontPath, int fontSize, SDL_Color textColor,
                  SDL2pp::Renderer &renderer);

    void setColorMod(const std::string &id, Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);

    void resetColorMod(const std::string &id);
};


#endif //WORMS_TALLER_1_TEXTUREMANAGER_H
