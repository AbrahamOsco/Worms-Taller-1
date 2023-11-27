//
// Created by riclui on 09/11/23.
//

#include "Input.h"

Input::Input() : m_quit(false), m_mouseLeftButtonDown(false), m_mouseRightButtonDown(false),
    m_mouseX(0), m_mouseY(0) {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_quit = true;
                break;
            case SDL_KEYDOWN:
                keyDown();
                break;
            case SDL_KEYUP:
                keyUp();
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseButtonDown(event);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseButtonUp(event);
                break;
            case SDL_MOUSEMOTION:
                mouseMotion(event);
                break;
                // Puedes agregar más casos según sea necesario
        }
    }
}

void Input::keyUp() {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown() {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::mouseButtonDown(SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseLeftButtonDown = true;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseRightButtonDown = true;
    }
    m_mouseX = event.button.x;
    m_mouseY = event.button.y;
}

void Input::mouseButtonUp(SDL_Event& event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        m_mouseLeftButtonDown = false;
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
        m_mouseRightButtonDown = false;
    }
    m_mouseX = event.button.x;
    m_mouseY = event.button.y;
}

void Input::mouseMotion(SDL_Event& event) {
    m_mouseX = event.motion.x;
    m_mouseY = event.motion.y;
}

bool Input::getKeyDown(SDL_Scancode key) const {
    return (m_keyStates[key] == 1);
}

bool Input::isMouseLeftButtonDown() const {
    return m_mouseLeftButtonDown;
}

bool Input::isMouseRightButtonDown() const {
    return m_mouseRightButtonDown;
}

int Input::getMouseX() const {
    return m_mouseX;
}

int Input::getMouseY() const {
    return m_mouseY;
}

bool Input::closed() const {
    return m_quit;
}

bool Input::getKeyUp(SDL_Scancode key) {
    return (m_keyStates[key] == 0);
}

void Input::setPress(bool pressed) {
    m_press = pressed;
}

bool Input::getPress() const {
    return m_press;
}