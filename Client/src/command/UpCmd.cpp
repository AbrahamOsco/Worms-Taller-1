//
// Created by riclui on 14/11/23.
//

#include "UpCmd.h"

void UpCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::UP_CMD);
    protocol.sendCommandDTO(commandDto);
}
