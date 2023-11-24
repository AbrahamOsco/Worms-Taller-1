//
// Created by riclui on 16/11/23.
//

#include "Camera.h"
#include "../utils/Constants.h"

Camera::Camera() : m_viewBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT){}

SDL2pp::Rect Camera::getViewBox() {
    return m_viewBox;
}

SDL2pp::Point Camera::getPosition() {
    return m_position;
}

void Camera::setTarget(SDL2pp::Point &target) {
    m_target.SetX(target.GetX());
    m_target.SetY(target.GetY());
}

void Camera::update() {
    m_viewBox.SetX(m_target.GetX() - WINDOW_WIDTH / 2);
    m_viewBox.SetY(m_target.GetY() - WINDOW_HEIGHT / 2);

    if (m_viewBox.GetX() < 0) {
        m_viewBox.SetX(0);
    }

    if (m_viewBox.GetY() < 0) {
        m_viewBox.SetY(0);
    }

    if (m_viewBox.GetX() + m_viewBox.GetW() > LEVEL_WIDTH) {
        m_viewBox.SetX(LEVEL_WIDTH - m_viewBox.GetW());
    }

    if (m_viewBox.GetY() + m_viewBox.GetH() > LEVEL_HEIGHT) {
        m_viewBox.SetY(LEVEL_HEIGHT - m_viewBox.GetH());
    }

    m_position = SDL2pp::Point(m_viewBox.GetX(),m_viewBox.GetY());
}
