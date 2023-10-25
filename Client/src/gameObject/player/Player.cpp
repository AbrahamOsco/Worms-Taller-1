//
// Created by riclui on 25/10/23.
//

#include "Player.h"

Player::Player(const LoaderParams &params) : GameObject(params) {
    m_animation.setProps(m_textureID, 14, 80, SDL_FLIP_HORIZONTAL);
}

void Player::draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    //m_animation.draw(m_transform.getX(), m_transform.getY(), m_width, m_height, renderer, textureManager);
    m_animation.draw(0, 0, m_width, m_height, renderer, textureManager);
}

void Player::update(float dt) {
    //m_rigidBody.applyForceX(8);
    //m_rigidBody.update(dt);
    //m_transform.translateX(m_rigidBody.position().getX());
    //m_transform.translateY(m_rigidBody.position().getY());

    m_animation.update();
}