//
// Created by riclui on 25/10/23.
//

#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {}

void SpriteAnimation::update() {
    m_currentFrame = (int) (SDL_GetTicks() / m_speed) % m_frameCount;
}

void SpriteAnimation::draw(int x, int y, int width, int height, SDL2pp::Renderer &renderer,
                           TextureManager &textureManager, SDL_RendererFlip flip, float xScale, float yScale) {
    textureManager.drawFrame(m_textureId, x, y, width, height, m_currentFrame, 0, renderer, flip);
}

void SpriteAnimation::setProps(const std::string &textureID, int frameCount,
                               int animSpeed) {
    m_speed = animSpeed;
    m_textureId = textureID;
    m_frameCount = frameCount;
}
