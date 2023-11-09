//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_INPUT_H
#define WORMS_TALLER_1_INPUT_H

#include "SDL2pp/SDL2pp.hh"

class Input {
private:
    const Uint8* m_keyStates;

    void keyUp();
    void keyDown();

    bool m_quit;

public:
    Input();
    void listen();
    bool getKeyDown(SDL_Scancode key);

    bool closed();
};

#endif //WORMS_TALLER_1_INPUT_H
