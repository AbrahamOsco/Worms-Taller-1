//
// Created by riclui on 21/11/23.
//

#include "SelectMortarCmd.h"

void SelectMortarCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_MORTAR);
    protocol.sendCommandDTO(commandDto);
}
