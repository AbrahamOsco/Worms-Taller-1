//
// Created by riclui on 25/10/23.
//

#ifndef WORMS_TALLER_1_TIMER_H
#define WORMS_TALLER_1_TIMER_H

#include "SDL2pp/SDL2pp.hh"

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
 private:
    float m_deltaTime;
    float m_lastTime;
 public:
    float getDeltaTime();
    void tick();
};


#endif  // WORMS_TALLER_1_TIMER_H
