//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_INPUT_H
#define WORMS_TALLER_1_INPUT_H

#include "SDL2pp/SDL2pp.hh"

class Input {
private:
    const Uint8* m_keyStates;
    bool m_quit;
    bool m_prevSpaceState;

    // Nuevas variables para el manejo del clic del mouse
    bool m_mouseLeftButtonDown;
    bool m_mouseRightButtonDown;
    int m_mouseX;
    int m_mouseY;

    void keyUp();
    void keyDown();
    void mouseButtonDown(SDL_Event& event);
    void mouseButtonUp(SDL_Event& event);
    void mouseMotion(SDL_Event& event);

public:
    Input();
    void listen();
    bool getKeyDown(SDL_Scancode key) const;
    bool getKeyUp(SDL_Scancode key);

    bool isMouseLeftButtonDown() const;
    bool isMouseRightButtonDown() const;
    int getMouseX() const;
    int getMouseY() const;

    bool closed() const;

    bool getPrevSpaceState();
};

#endif //WORMS_TALLER_1_INPUT_H
