//
// Created by riclui on 11/11/23.
//

#include "SelectTeleportCmd.h"

void SelectTeleportCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_TELEPORT);
    protocol.sendCommandDTO(commandDto);
}
