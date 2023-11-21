//
// Created by riclui on 14/11/23.
//

#include "Projectile.h"

Projectile::Projectile(int x, int y, const TypeProjectil &typeProjectile, const TypeFocus &typeFocus) : GameObject(LoaderParams(x, y, 15, 15, " ")),
                                                                            m_typeProjectile(typeProjectile), m_typeFocus(typeFocus) {
    if (m_typeProjectile == TypeProjectil::BAZOOKA_PROJECTILE) {
        m_textureID = "bazooka_projectile";
    } else if (m_typeProjectile == TypeProjectil::AIR_ATTACK_MISSILE) {
        m_textureID = "air_attack_projectile";
    } else if (m_typeProjectile == TypeProjectil::DYNAMITE) {
        m_textureID = "dynamite_projectile";
    } else {
        m_textureID = "mortar_projectile";
    }
}

void Projectile::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int posX = m_x - m_width / 2 - camera.getPosition().GetX();
    int posY = m_y - m_height / 2 - camera.getPosition().GetY();
    textureManager.draw(m_textureID, posX, posY, m_width, m_height, renderer, SDL_FLIP_NONE);
}

void
Projectile::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (m_typeFocus == TypeFocus::FOCUS) {
        SDL2pp::Point point(m_x, m_y);
        camera.setTarget(point);
    }
}
