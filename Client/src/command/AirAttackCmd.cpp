//
// Created by riclui on 20/11/23.
//

#include "AirAttackCmd.h"

AirAttackCmd::AirAttackCmd(int x, int y) : m_x(x), m_y(y) {}

void AirAttackCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setX(m_x);
    commandDto.setY(m_y);
    commandDto.setTypeCommand(TypeCommand::AIR_ATTACK_POINT);
    protocol.sendCommandDTO(commandDto);
}
