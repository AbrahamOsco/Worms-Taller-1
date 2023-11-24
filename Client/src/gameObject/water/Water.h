//
// Created by riclui on 23/11/23.
//

#ifndef WORMS_TALLER_1_WATER_H
#define WORMS_TALLER_1_WATER_H

#include "SDL2pp/SDL2pp.hh"
#include "../../graphics/TextureManager.h"

class Water {
private:
    std::string m_textureID;
    int m_width, m_height;
    int m_y;
public:
    explicit Water(int y);
    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager);

    void setY(int y);
};


#endif //WORMS_TALLER_1_WATER_H
