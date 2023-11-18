//
// Created by riclui on 17/11/23.
//

#include "SeqAnimation.h"

SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat) {

}

void SeqAnimation::update() {
    if (m_repeat || !m_isEnded) {
        m_isEnded = false;
        m_currentFrame = (int) (SDL_GetTicks() / m_speed) % m_frameCount;
    }

    if (!m_repeat && m_currentFrame == m_frameCount) {
        m_isEnded = true;
        m_currentFrame = m_frameCount;
    }
}

void SeqAnimation::setRepeat(bool repeat) {
    m_repeat = repeat;
}

void
SeqAnimation::drawFrame(int x, int y, int width, int height, SDL2pp::Renderer &renderer, TextureManager &textureManager,
                        SDL_RendererFlip flip, float xScale, float yScale) {
    textureManager.drawFrame(m_textureId, x, y, width, height, m_currentFrame, 0, renderer, flip);
}

void SeqAnimation::setProps(const std::string &textureID, int frameCount, int animSpeed) {
    m_speed = animSpeed;
    m_textureId = textureID;
    m_frameCount = frameCount;
}