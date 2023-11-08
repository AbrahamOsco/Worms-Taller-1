//
// Created by riclui on 31/10/23.
//

#include <iostream>
#include "LeftCmd.h"

void LeftCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::LEFT_CMD);
    protocol.sendCommandDTO(commandDto);
}
