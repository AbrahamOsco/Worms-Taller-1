//
// Created by riclui on 14/11/23.
//

#include "SelectBazooka.h"

void SelectBazooka::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setTypeCommand(TypeCommand::SELECT_BAZOOKA);
    protocol.sendCommandDTO(commandDto);
}
