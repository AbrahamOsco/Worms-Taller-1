//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_COMMAND_H
#define WORMS_TALLER_1_COMMAND_H


#include "../protocol/ClientProtocol.h"

class Command {
public:
    virtual void execute(ClientProtocol &protocol) = 0;
    virtual ~Command() = default;
};


#endif //WORMS_TALLER_1_COMMAND_H
