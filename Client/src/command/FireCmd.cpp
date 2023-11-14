//
// Created by riclui on 13/11/23.
//

#include "FireCmd.h"

void FireCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::FIRE_CMD);
    protocol.sendCommandDTO(commandDto);
}
