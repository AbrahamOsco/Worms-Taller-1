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
}
