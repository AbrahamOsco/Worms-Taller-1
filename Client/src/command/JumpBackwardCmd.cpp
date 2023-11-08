//
// Created by riclui on 07/11/23.
//

#include <iostream>
#include "JumpBackwardCmd.h"

void JumpBackwardCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::JUMP_BACK_CMD);
    protocol.sendCommandDTO(commandDto);
}
