//
// Created by riclui on 14/11/23.
//

#include "Projectile.h"

Projectile::Projectile(int x, int y, const TypeProjectil &typeProjectile) : GameObject(LoaderParams(x, y, 15, 15, " ")), m_typeProjectile(typeProjectile){
    if (m_typeProjectile == TypeProjectil::BAZOOKA_PROJECTILE) {
        m_textureID = "bazooka_projectile";
    } else {
        m_textureID = "mortar_projectile";
    }
}

void Projectile::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    textureManager.draw(m_textureID, m_x - m_width / 2, m_y - m_height / 2, m_width, m_height, renderer, SDL_FLIP_NONE);
}
