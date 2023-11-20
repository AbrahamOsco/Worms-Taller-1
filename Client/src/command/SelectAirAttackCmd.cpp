//
// Created by riclui on 20/11/23.
//

#include "SelectAirAttackCmd.h"

void SelectAirAttackCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_AIR_ATTACK);
    protocol.sendCommandDTO(commandDto);
}
