//
// Created by riclui on 25/10/23.
//

#include "SpriteAnimation.h"

void SpriteAnimation::update() {
    m_SpriteFrame = (int)(SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void SpriteAnimation::draw(int x, int y, SDL_RendererFlip flip, SDL2pp::Renderer &renderer, TextureManager &textureManager,
                           Camera &camera) {
    textureManager.drawFrame(m_TextureID, x, y, m_spriteWidth, m_spriteHeight, m_SpriteFrame, 0, renderer, flip, camera);
}

void SpriteAnimation::setProps(const std::string &textureID, int spriteWidth, int spriteHeight, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_spriteWidth = spriteWidth;
    m_spriteHeight = spriteHeight;
    m_TextureID = textureID;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}
