//
// Created by riclui on 21/11/23.
//

#include "SelectGreenGrenadeCmd.h"

void SelectGreenGrenadeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_GREEN_GRENADE);
    protocol.sendCommandDTO(commandDto);
}
