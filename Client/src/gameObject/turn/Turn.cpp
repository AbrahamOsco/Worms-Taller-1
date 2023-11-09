//
// Created by riclui on 06/11/23.
//

#include "Turn.h"
#include "../../command/RightCmd.h"
#include "../../command/LeftCmd.h"
#include "../../command/JumpForwardCmd.h"
#include "../../command/JumpBackwardCmd.h"

Turn::Turn(bool isTurn) : GameObject(), m_isTurn(isTurn) {}

void Turn::update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) {
    if (input.getKeyDown(SDL_SCANCODE_RIGHT)) {
        std::unique_ptr<Command> command(new RightCmd()); // Comando para mover a la derecha
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_LEFT)) {
        std::unique_ptr<Command> command(new LeftCmd()); // Comando para mover a la izquierda
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_RETURN)) {
        std::unique_ptr<Command> command(new JumpForwardCmd()); // Comando para saltar hacia adelante
        queue.move_push(std::move(command));
    } else if (input.getKeyDown(SDL_SCANCODE_BACKSPACE)) {
        std::unique_ptr<Command> command(new JumpBackwardCmd()); // Comando para saltar hacia atrás
        queue.move_push(std::move(command));
    }

}
