//
// Created by riclui on 07/11/23.
//

#ifndef WORMS_TALLER_1_JUMPBACKWARDCMD_H
#define WORMS_TALLER_1_JUMPBACKWARDCMD_H


#include "Command.h"

class JumpBackwardCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_JUMPBACKWARDCMD_H
