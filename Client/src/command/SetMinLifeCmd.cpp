//
// Created by riclui on 22/11/23.
//

#include "SetMinLifeCmd.h"

void SetMinLifeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::MIN_LIFE);
    protocol.sendCommandDTO(commandDto);
}
