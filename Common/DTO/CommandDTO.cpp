//
// Created by riclui on 06/11/23.
//

#include "CommandDTO.h"

CommandDTO::CommandDTO() : DTO(COMMAND), m_typeCommand(NONE), m_x(0), m_y(0) {}

void CommandDTO::setTypeCommand(const TypeCommand &typeCommand) {
    m_typeCommand = typeCommand;
}

TypeCommand CommandDTO::getTypeCommand() const {
    return m_typeCommand;
}

int CommandDTO::getX() const {
    return m_x;
}

int CommandDTO::getY() const {
    return m_y;
}

void CommandDTO::setX(int x) {
    m_x = x;
}

void CommandDTO::setY(int y) {
    m_y = y;
}

bool CommandDTO::operator==(const CommandDTO& other) const {
    return  this->opType == other.opType &&
            this->m_typeCommand == other.m_typeCommand &&
            this->m_x == other.m_x &&
            this->m_y == other.m_y;
}



