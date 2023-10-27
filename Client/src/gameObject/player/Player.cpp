//
// Created by riclui on 25/10/23.
//

#include "Player.h"

Player::Player(const LoaderParams &params) : GameObject(params) {
    m_flip = SDL_FLIP_NONE;
    m_animation.setProps(m_textureID, m_width, m_height, 14, 80);
}

void Player::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    m_animation.draw(0, 0, m_flip,renderer, textureManager);
}

void Player::update(float dt) {
    m_animation.update();
}