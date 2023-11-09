//
// Created by riclui on 25/10/23.
//

#include "Worm.h"

Worm::Worm(const LoaderParams &params, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
           const MoveWorm &moveWorm) : GameObject(params), m_hpWorm(hpWorm), m_directionLook(direction),
                                       m_typeFocus(focus), m_moveWorm(moveWorm) {
    m_flip = SDL_FLIP_NONE;
    m_animation.setProps(m_textureID, m_width, m_height, 14, 80);
}

void Worm::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    SDL_Color textColor = {225, 225, 225, 255};
    SDL_Color boxColor = {0, 0, 0, 255};
    std::string fontPath = "../Client/resources/fonts/GROBOLD.ttf";
    textureManager.drawText(std::to_string(m_hpWorm), m_x - 20, m_y - 30, 36, 15, fontPath, 11, textColor, boxColor,
                            renderer);
    m_animation.draw(m_x - m_width / 2, m_y - m_height / 2, m_flip, renderer, textureManager);
}

void Worm::update(float dt) {
    if (m_directionLook == Direction::RIGHT) {
        m_flip = SDL_FLIP_HORIZONTAL;
    }
    m_animation.update();
    animationState();
}

void Worm::animationState() {
    m_animation.setProps("player", m_width, m_height, 14, 80, SDL_FLIP_NONE);

    if (m_moveWorm == MoveWorm::WALKING) {
        m_width = 30;
        m_height = 30;
        m_animation.setProps("walk", m_width, m_height, 14, 80, SDL_FLIP_NONE);
    }
    if (m_moveWorm == MoveWorm::JUMPING) {
        m_width = 60;
        m_height = 60;
        m_animation.setProps("air", m_width, m_height, 36, 80, SDL_FLIP_NONE);
    }
}
