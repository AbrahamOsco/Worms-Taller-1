//
// Created by riclui on 11/11/23.
//

#include "SelectBatCmd.h"

void SelectBatCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_BAT);
    protocol.sendCommandDTO(commandDto);
}

