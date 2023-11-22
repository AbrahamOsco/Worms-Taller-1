//
// Created by riclui on 22/11/23.
//

#include "SetMaxLifeCmd.h"

void SetMaxLifeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::MAX_LIFE);
    protocol.sendCommandDTO(commandDto);
}
