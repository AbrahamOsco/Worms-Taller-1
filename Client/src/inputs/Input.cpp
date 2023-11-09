//
// Created by riclui on 09/11/23.
//

#include "Input.h"

Input::Input() : m_quit(false) {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::listen() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: m_quit = true;
                break;
            case SDL_KEYDOWN: keyDown();
                break;
            case SDL_KEYUP: keyUp();
                break;
        }
    }
}

bool Input::getKeyDown(SDL_Scancode key) {
    return (m_keyStates[key] == 1);
}

void Input::keyUp() {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown() {
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

bool Input::closed() {
    return m_quit;
}