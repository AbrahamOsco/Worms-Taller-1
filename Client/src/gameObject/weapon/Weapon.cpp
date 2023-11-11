//
// Created by riclui on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(TypeWeapon typeWeapon, int ammoCount) : GameObject(LoaderParams(0, 0, 50, 55, " ")),
                                                        m_typeWeapon(typeWeapon), m_ammoCount(ammoCount) {
    if (m_typeWeapon == TypeWeapon::AIR_ATTACK) {
        m_textureID = "air_attack_icon";
    } else if (m_typeWeapon == TypeWeapon::DYNAMITE) {
        m_textureID = "dynamite_icon";
    } else if (m_typeWeapon == TypeWeapon::RED_GRENADE) {
        m_textureID = "red_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::GREEN_GRENADE) {
        m_textureID = "green_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::BANANA) {
        m_textureID = "banana_icon";
    } else if (m_typeWeapon == TypeWeapon::TELEPORT) {
        m_textureID = "teleportation_icon";
    } else if (m_typeWeapon == TypeWeapon::BASEBALL_BAT) {
        m_textureID = "bat_icon";
    } else if (m_typeWeapon == TypeWeapon::HOLY_GRENADE) {
        m_textureID = "holy_grenade_icon";
    } else if (m_typeWeapon == TypeWeapon::BAZOOKA) {
        m_textureID = "bazzoka_icon";
    } else if (m_typeWeapon == TypeWeapon::MORTAR) {
        m_textureID = "mortar_icon";
    }
}

void Weapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    SDL_Color textColor = {0, 0, 0, 255};
    int fontSize = 16;
    int padding = 6;
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);
    textureManager.drawText("Ammo:", m_x + m_width + padding, m_y + 12, fontPath, fontSize, textColor, renderer);
    textureManager.drawText(std::to_string(m_ammoCount), m_x + m_width + 20, m_y + 32, fontPath, fontSize, textColor,
                            renderer);
}

void Weapon::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int Weapon::getHeight() {
    return m_height;
}


