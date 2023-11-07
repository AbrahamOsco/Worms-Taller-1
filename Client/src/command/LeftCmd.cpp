//
// Created by riclui on 31/10/23.
//

#include <iostream>
#include "LeftCmd.h"

void LeftCmd::execute(ClientProtocol &protocol) {
    std::cout << "sending: move left" << std::endl;
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::LEFT_CMD);
    protocol.sendCommandDTO(commandDto);
}
