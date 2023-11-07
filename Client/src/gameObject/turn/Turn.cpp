//
// Created by riclui on 06/11/23.
//

#include "Turn.h"
#include "../../command/RightCmd.h"
#include "../../command/LeftCmd.h"

Turn::Turn(bool isTurn) : GameObject(), m_isTurn(isTurn) {}

void Turn::processEvent(SDL_Event &event, Queue<std::unique_ptr<Command>> &queue) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
            std::unique_ptr<Command> command(new RightCmd()); // Comando para mover a la derecha
            queue.move_push(std::move(command));
        } else if (event.key.keysym.sym == SDLK_LEFT) {
            std::unique_ptr<Command> command(new LeftCmd()); // Comando para mover a la izquierda
            queue.move_push(std::move(command));
        }
    }
}
