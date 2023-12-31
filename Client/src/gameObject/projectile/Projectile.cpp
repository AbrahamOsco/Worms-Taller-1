//
// Created by riclui on 14/11/23.
//

#include "Projectile.h"

Projectile::Projectile(int x, int y, const TypeProjectil &typeProjectile, const TypeFocus &typeFocus,
                       const TypeExplode &typeExplode) : GameObject(LoaderParams(x, y, 15, 15, " ")),
                                                         m_typeProjectile(typeProjectile), m_typeFocus(typeFocus),
                                                         m_typeExplode(typeExplode),
                                                         m_animation(true) {
    m_animation.setProps("explosion", 30, 60);
    if (m_typeProjectile == TypeProjectil::BAZOOKA_PROJECTILE) {
        m_textureID = "bazooka_projectile";
    } else if (m_typeProjectile == TypeProjectil::AIR_ATTACK_MISSILE) {
        m_textureID = "air_attack_projectile";
    } else if (m_typeProjectile == TypeProjectil::DYNAMITE) {
        m_textureID = "dynamite_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_GREEN_GRENADE) {
        m_textureID = "green_grenade_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_RED_GRENADE) {
        m_textureID = "red_grenade_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_BANANA) {
        m_textureID = "banana_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_MORTAR) {
        m_textureID = "mortar_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_HOLY_GRENADE) {
        m_textureID = "holy_grenade_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_MORTAR_FRAGMENT) {
        m_textureID = "mortar_fragment_projectile";
    } else if (m_typeProjectile == TypeProjectil::PROJ_RED_GRENADE_FRAGMENT) {
        m_textureID = "red_grenade_fragment_projectile";
    } else if (m_typeExplode == TypeExplode::EXPLODE) {
        m_textureID = "explosion";
        m_width = 60;
        m_height = 60;
        m_animation.setProps("explosion", 12, 30);
    }
}

void Projectile::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int posX = m_x - m_width / 2 - camera.getPosition().GetX();
    int posY = m_y - m_height / 2 - camera.getPosition().GetY();
    if (m_typeExplode == TypeExplode::NO_EXPLODE) {
        textureManager.draw(m_textureID, posX, posY, m_width, m_height, renderer, SDL_FLIP_NONE);
    } else if (m_typeExplode == TypeExplode::EXPLODE) {
        textureManager.drawFrame("explosion", posX, posY, 60, 60, 0, 0, renderer, SDL_FLIP_NONE);
    }
}

void
Projectile::update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) {
    if (m_typeFocus == TypeFocus::FOCUS) {
        SDL2pp::Point point(m_x, m_y);
        camera.setTarget(point);
    }

    if (m_typeExplode == TypeExplode::EXPLODE_SOUND) {
        if (m_typeProjectile == TypeProjectil::PROJ_HOLY_GRENADE) {
            soundManager.playEffect("holy_grenade");
        } else {
            soundManager.playEffect("explosion");
        }
    }
}
