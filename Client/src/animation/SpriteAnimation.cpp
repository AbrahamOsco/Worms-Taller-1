//
// Created by riclui on 25/10/23.
//

#include "SpriteAnimation.h"

void SpriteAnimation::update() {
    m_SpriteFrame = (int) (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void SpriteAnimation::draw(int x, int y, int spriteWidth, int spriteHeight, Camera &camera, SDL2pp::Renderer &renderer,
                           TextureManager &textureManager, SDL_RendererFlip flip, float xScale, float yScale) {
    textureManager.drawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteFrame, 0, renderer, flip, camera);
}

void SpriteAnimation::setProps(const std::string &textureID, int frameCount,
                               int animSpeed) {
    m_TextureID = textureID;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
}

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {}
