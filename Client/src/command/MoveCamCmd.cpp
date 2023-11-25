//
// Created by riclui on 24/11/23.
//

#include "MoveCamCmd.h"

void MoveCamCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::MOVE_CAM);
    protocol.sendCommandDTO(commandDto);
}
