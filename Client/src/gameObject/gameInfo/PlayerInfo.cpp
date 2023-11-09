//
// Created by riclui on 09/11/23.
//

#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(int id, const std::string &name, int totalLife) : GameObject(LoaderParams(0, 0, 40, 20, " ")),
                                                                         m_id(id),
                                                                         m_name(name),
                                                                         m_totalLife(totalLife) {}

void PlayerInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    int fontSize = 12;
    int padding = 10;
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawTextBox(std::to_string(m_id), m_x, m_y, fontPath, fontSize, textColor, boxColor, renderer);
    std::string text = m_name + ": " + std::to_string(m_totalLife);
    textureManager.drawText(text, m_x + padding, m_y, fontPath, fontSize, boxColor, renderer);
}

void PlayerInfo::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int PlayerInfo::getHeight() {
    return m_height;
}
