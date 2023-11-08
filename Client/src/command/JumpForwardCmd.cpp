//
// Created by riclui on 07/11/23.
//

#include <iostream>
#include "JumpForwardCmd.h"

void JumpForwardCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    std::cout << "send: jump_forward" << std::endl;
    commandDto.setTypeCommand(TypeCommand::JUMP_FORWARD_CMD);
    protocol.sendCommandDTO(commandDto);
}
