//
// Created by riclui on 09/11/23.
//

#include "PlayerInfo.h"
#include "../../utils/ColorDefinitions.h"

PlayerInfo::PlayerInfo(int id, const std::string &name, int totalLife) : GameObject(LoaderParams(0, 0, 40, 18, " ")),
                                                                         m_id(id),
                                                                         m_name(name),
                                                                         m_totalLife(totalLife) {}

void PlayerInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int fontSize = 16;
    int padding = 20;
    SDL_Color textBoxColor = {225, 225, 225, 255};
    SDL_Color boxColorInfo = {255, 255, 255, 80};
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color boxColor = colorMap[static_cast<ColorID>(m_id)];
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawTextBox(std::to_string(m_id), m_x, m_y, fontPath, fontSize, textBoxColor, boxColor, renderer);
    std::string text = m_name + ": " + std::to_string(m_totalLife);
    textureManager.drawTextBox(text, m_x + padding, m_y, fontPath, fontSize, textColor, boxColorInfo,renderer);
}

void PlayerInfo::setParams(int x, int y) {
    m_x = x;
    m_y = y;
}

int PlayerInfo::getHeight() {
    return m_height;
}
