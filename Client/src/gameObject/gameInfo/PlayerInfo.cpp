//
// Created by riclui on 09/11/23.
//

#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(int id, const std::string &name, int totalLife) : GameObject(LoaderParams(0, 0, 40, 20, " ")),
                                                                         m_id(id),
                                                                         m_name(name),
                                                                         m_totalLife(totalLife) {}

void PlayerInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawBoxText(m_name, m_x, m_y, m_width, m_height, fontPath, 12, textColor, boxColor, renderer);
}

void PlayerInfo::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int PlayerInfo::getHeight() {
    return m_height;
}
