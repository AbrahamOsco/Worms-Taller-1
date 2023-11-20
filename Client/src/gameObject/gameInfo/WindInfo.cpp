//
// Created by riclui on 09/11/23.
//

#include "WindInfo.h"

WindInfo::WindInfo(int velocity, TypeWind direction) : GameObject(LoaderParams(10, 40, 34, 18, "arrow_no")),
                                                                                    m_velocity(velocity),
                                                                                    m_direction(direction) {
    if (m_direction == TypeWind::WIND_RIGHT) {
        m_textureID = "arrow_right";
        m_width = 50;
    }
    if (m_direction == TypeWind::WIND_LEFT) {
        m_width = 50;
        m_textureID = "arrow_left";
    }
}

void WindInfo::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) {
    int fontSize = 16;
    SDL_Color textColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawText("Wind", m_x, m_y, fontPath, fontSize, textColor, renderer);
    textureManager.drawText(std::to_string(m_velocity), m_x, m_y + 20, fontPath, fontSize, textColor, renderer);
    textureManager.draw(m_textureID, m_x, m_y + 40, m_width, m_height, renderer, SDL_FLIP_NONE);
}
