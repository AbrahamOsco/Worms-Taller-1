//
// Created by riclui on 06/11/23.
//

#include "CommandDTO.h"

CommandDTO::CommandDTO() : DTO(COMMAND), m_typeCommand(NONE){}

void CommandDTO::setTypeCommand(const TypeCommand &typeCommand) {
    m_typeCommand = typeCommand;
}

TypeCommand CommandDTO::getTypeCommand() const {
    return m_typeCommand;
}



