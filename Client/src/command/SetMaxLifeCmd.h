//
// Created by riclui on 22/11/23.
//

#ifndef WORMS_TALLER_1_SETMAXLIFECMD_H
#define WORMS_TALLER_1_SETMAXLIFECMD_H


#include "Command.h"

class SetMaxLifeCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_SETMAXLIFECMD_H
