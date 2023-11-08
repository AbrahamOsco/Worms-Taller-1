//
// Created by riclui on 31/10/23.
//

#include <iostream>
#include "RightCmd.h"

void RightCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::RIGHT_CMD);
    protocol.sendCommandDTO(commandDto);
}
