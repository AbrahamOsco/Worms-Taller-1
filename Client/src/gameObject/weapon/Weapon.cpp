//
// Created by riclui on 09/11/23.
//

#include "Weapon.h"

Weapon::Weapon(const std::string &weapon, int ammoCount) : GameObject(LoaderParams(0, 0, 50, 55, weapon)),
                                                           m_ammoCount(ammoCount) {}

void Weapon::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    SDL_Color textColor = {0, 0, 0, 255};
    int fontSize = 16;
    int padding = 6;
    textureManager.draw(m_textureID, m_x, m_y, m_width, m_height, renderer, SDL_FLIP_NONE);
    textureManager.drawText("Ammo:", m_x + m_width + padding, m_y + 12, fontPath, fontSize, textColor, renderer);
    textureManager.drawText(std::to_string(m_ammoCount), m_x + m_width + 20, m_y + 32 , fontPath, fontSize, textColor, renderer);
}

void Weapon::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int Weapon::getHeight() {
    return m_height;
}


