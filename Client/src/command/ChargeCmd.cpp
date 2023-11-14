//
// Created by riclui on 13/11/23.
//

#include "ChargeCmd.h"

void ChargeCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::CHARGE_CMD);
    protocol.sendCommandDTO(commandDto);
}
