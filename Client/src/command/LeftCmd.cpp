//
// Created by riclui on 31/10/23.
//

#include <iostream>
#include "LeftCmd.h"

void LeftCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    std::cout << "send: left" << std::endl;
    commandDto.setTypeCommand(TypeCommand::LEFT_CMD);
    protocol.sendCommandDTO(commandDto);
}
