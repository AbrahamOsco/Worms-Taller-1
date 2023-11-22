//
// Created by riclui on 22/11/23.
//

#ifndef WORMS_TALLER_1_SETMINLIFECMD_H
#define WORMS_TALLER_1_SETMINLIFECMD_H


#include "Command.h"

class SetMinLifeCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SETMINLIFECMD_H
