//
// Created by riclui on 21/11/23.
//

#include "SelectBananaCmd.h"

void SelectBananaCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_BANANA);
    protocol.sendCommandDTO(commandDto);
}
