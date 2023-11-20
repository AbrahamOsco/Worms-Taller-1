//
// Created by riclui on 20/11/23.
//

#include "Provision.h"

Provision::Provision(int x, int y, const TypeEffect &typeEffect) : GameObject(LoaderParams(x, y, 27, 32, "box")), m_typeEffect(typeEffect) {}

void Provision::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();
    textureManager.draw(m_textureID, xCorrection, yCorrection, m_width, m_height, renderer);
}
