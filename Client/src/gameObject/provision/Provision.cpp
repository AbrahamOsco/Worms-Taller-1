//
// Created by riclui on 20/11/23.
//

#include "Provision.h"

Provision::Provision(int x, int y, const TypeEffect &typeEffect, const TypeContact &typeContact) : GameObject(LoaderParams(x, y, 27, 32, "box")), m_typeEffect(typeEffect), m_typeContact(typeContact) {}

void Provision::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int xCorrection = m_x - m_width / 2 - camera.getPosition().GetX();
    int yCorrection = m_y - m_height / 2 - camera.getPosition().GetY();
    if (m_typeContact == TypeContact::NO_CONTACT ) {
        textureManager.draw(m_textureID, xCorrection, yCorrection, m_width, m_height, renderer);
    } else if (m_typeContact == TypeContact::CONTACT && m_typeEffect == TypeEffect::EXPLOSION) {
        textureManager.drawFrame("explosion", xCorrection, yCorrection, 60, 60, 0, 0,renderer,SDL_FLIP_NONE);
    }

}

void
Provision::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (m_typeContact == TypeContact::CONTACT_SOUND && m_typeEffect == TypeEffect::EXPLOSION) {
        soundManager.playEffect("explosion");
    }
}
