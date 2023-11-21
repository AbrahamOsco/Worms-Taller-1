//
// Created by riclui on 21/11/23.
//

#include "CountdownCmd.h"

CountdownCmd::CountdownCmd(int count) : m_count(count) {}

void CountdownCmd::execute(ClientProtocol &protocol) {
    CommandDTO commandDto;
    commandDto.setX(m_count);
    commandDto.setTypeCommand(TypeCommand::COUNTDOWN);
    protocol.sendCommandDTO(commandDto);
}
