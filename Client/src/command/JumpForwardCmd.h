//
// Created by riclui on 07/11/23.
//

#ifndef WORMS_TALLER_1_JUMPFORWARDCMD_H
#define WORMS_TALLER_1_JUMPFORWARDCMD_H


#include "Command.h"

class JumpForwardCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_JUMPFORWARDCMD_H
