//
// Created by riclui on 21/11/23.
//

#include "SelectHolyGrenadeCmd.h"

void SelectHolyGrenadeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_HOLY_GRENADE);
    protocol.sendCommandDTO(commandDto);
}
