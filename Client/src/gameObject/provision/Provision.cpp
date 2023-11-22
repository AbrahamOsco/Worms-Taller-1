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
    } else if (m_typeContact == TypeContact::CONTACT) {
        if (m_typeEffect == TypeEffect::EXPLOSION) {
            textureManager.drawFrame("explosion", xCorrection, yCorrection, 60, 60, 0, 0,renderer,SDL_FLIP_NONE);
        } else if (m_typeEffect == TypeEffect::MEDICAL_KIT) {
            textureManager.drawFrame("medicine", xCorrection, yCorrection, 30, 30, 0, 0,renderer,SDL_FLIP_NONE);
        } else if (m_typeEffect == TypeEffect::MUNITIONS) {
            textureManager.drawFrame("munition", xCorrection, yCorrection, 37, 42, 0, 0,renderer,SDL_FLIP_NONE);
        }
    }
}

void
Provision::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (m_typeContact == TypeContact::CONTACT_SOUND) {
        if (m_typeEffect == TypeEffect::EXPLOSION) {
            soundManager.playEffect("explosion");
        } else if (m_typeEffect == TypeEffect::MEDICAL_KIT) {
            soundManager.playEffect("collect_medicine");
        }else if (m_typeEffect == TypeEffect::MUNITIONS) {
            soundManager.playEffect("collect_weapon");
        }
    }
}
