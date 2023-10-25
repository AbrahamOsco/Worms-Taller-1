//
// Created by riclui on 25/10/23.
//

#include "Timer.h"

void Timer::tick() {
    m_deltaTime = (SDL_GetTicks() - m_lastTime) * (TARGET_FPS/1000.0f);

    if(m_deltaTime > TARGET_DELTATIME) {
        m_deltaTime = TARGET_DELTATIME;
    }

    m_lastTime = SDL_GetTicks();
}

float Timer::getDeltaTime() {
    return m_deltaTime;
}
