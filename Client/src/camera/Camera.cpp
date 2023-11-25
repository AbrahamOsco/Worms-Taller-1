//
// Created by riclui on 16/11/23.
//

#include "Camera.h"
#include "../utils/Constants.h"
#include "../inputs/Input.h"
#include "../../../Common/Queue/Queue.h"
#include "../command/MoveCamCmd.h"

Camera::Camera() : m_viewBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), m_target(0,0){}

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

void Camera::update(Input &input, Queue<std::unique_ptr<Command>> &queue) {
    if (input.getKeyDown(SDL_SCANCODE_D)) {
        m_target.SetX(m_target.GetX() + 5);
        std::unique_ptr<Command> command(new MoveCamCmd());
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_A)) {
        m_target.SetX(m_target.GetX() - 5);
        std::unique_ptr<Command> command(new MoveCamCmd());
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_S)) {
        m_target.SetY(m_target.GetY() + 5);
        std::unique_ptr<Command> command(new MoveCamCmd());
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_W)) {
        m_target.SetY(m_target.GetY() - 5);
        std::unique_ptr<Command> command(new MoveCamCmd());
        queue.move_push(std::move(command));
    }

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
