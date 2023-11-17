//
// Created by riclui on 17/11/23.
//

#include "Animation.h"

Animation::Animation(bool repeat) : m_repeat(repeat), m_isEnded(false), m_currentFrame(0) {}

bool Animation::isEnded() {
    return m_isEnded;
}
