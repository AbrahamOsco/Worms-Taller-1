//
// Created by riclui on 21/11/23.
//

#include "SelectDynamiteCmd.h"

void SelectDynamiteCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_DYNAMITE);
    protocol.sendCommandDTO(commandDto);
}
