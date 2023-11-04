//
// Created by riclui on 25/10/23.
//

#include "Worm.h"

Worm::Worm(const LoaderParams &params) : GameObject(params) {
    m_flip = SDL_FLIP_NONE;
    m_animation.setProps(m_textureID, m_width, m_height, 14, 80);
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    m_animation.draw(m_x, m_y, m_flip,renderer, textureManager);
}

void Worm::update(float dt) {
    m_animation.update();
}