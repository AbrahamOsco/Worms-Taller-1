//
// Created by riclui on 25/10/23.
//

#include "Animation.h"

void Animation::update() {
    m_SpriteFrame = (int)(SDL_GetTicks()/m_AnimSpeed) % m_FrameCount;
}

void Animation::draw(int x, int y, int spritWidth, int spriteHeight, SDL2pp::Renderer &renderer, TextureManager &textureManager) {
    textureManager.drawFrame(m_TextureID, x, y, spritWidth, spriteHeight, m_SpriteFrame, 0, renderer, m_Flip);
}

void Animation::setProps(std::string &textureID, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_TextureID = textureID;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}
