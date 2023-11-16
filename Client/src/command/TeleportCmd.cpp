//
// Created by riclui on 16/11/23.
//

#include "TeleportCmd.h"

void TeleportCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setX(m_x);
    commandDto.setY(m_y);
    commandDto.setTypeCommand(TypeCommand::TELEPORT_MOVE);
    protocol.sendCommandDTO(commandDto);
}

TeleportCmd::TeleportCmd(int x, int y) : m_x(x), m_y(y) {}
