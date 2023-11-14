//
// Created by riclui on 14/11/23.
//

#include "DownCmd.h"

void DownCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::DOWN_CMD);
    protocol.sendCommandDTO(commandDto);
}
