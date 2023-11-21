//
// Created by riclui on 21/11/23.
//

#include "SelectRedGrenadeCmd.h"

void SelectRedGrenadeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_RED_GRENADE);
    protocol.sendCommandDTO(commandDto);
}
