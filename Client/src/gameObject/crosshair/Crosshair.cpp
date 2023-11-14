//
// Created by riclui on 13/11/23.
//

#include "Crosshair.h"

Crosshair::Crosshair(int x, int y, const TypeSight &typeSight) : GameObject(LoaderParams(x, y, 60, 60, "crosshair")), m_typeSight(typeSight) {
    m_animation.setProps(m_textureID, m_width, m_height, 32, 60);
}

void Crosshair::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    if (m_typeSight == TypeSight::SHOW_SIGHT) {
        m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_flip, renderer, textureManager);
    }
}

void Crosshair::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    m_animation.update();
}

