//
// Created by riclui on 06/11/23.
//

#ifndef WORMS_TALLER_1_COMMANDDTO_H
#define WORMS_TALLER_1_COMMANDDTO_H


#include <cstddef>
#include "DTO.h"

enum TypeCommand {
    LEFT_CMD,
    RIGHT_CMD,
    JUMP_BACK_CMD,
    JUMP_FORWARD_CMD,
    NONE
};

class CommandDTO : public DTO {
private:
    TypeCommand m_typeCommand;
public:
    CommandDTO();
    void setTypeCommand(const TypeCommand& typeCommand);
    TypeCommand getTypeCommand() const;
};


#endif //WORMS_TALLER_1_COMMANDDTO_H
