//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_LEFTCMD_H
#define WORMS_TALLER_1_LEFTCMD_H


#include "Command.h"

class LeftCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_LEFTCMD_H
