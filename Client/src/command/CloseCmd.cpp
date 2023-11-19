//
// Created by riclui on 19/11/23.
//

#include "CloseCmd.h"

void CloseCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::CLOSE_GAME);
    protocol.sendCommandDTO(commandDto);
}
