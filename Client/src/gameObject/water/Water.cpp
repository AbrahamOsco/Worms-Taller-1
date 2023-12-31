//
// Created by riclui on 23/11/23.
//

#include "Water.h"

Water::Water(int y) : m_y(y), m_height(1080), m_width(1920), m_textureID("water") {}

void Water::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int yCorrection = m_y - camera.getPosition().GetY();
    textureManager.draw(m_textureID, 0, yCorrection, m_width, m_height, renderer, SDL_FLIP_NONE);
}

void Water::setY(int y) {
    m_y = y;
}


