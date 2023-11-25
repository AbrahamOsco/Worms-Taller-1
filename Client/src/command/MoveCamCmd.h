//
// Created by riclui on 24/11/23.
//

#ifndef WORMS_TALLER_1_MOVECAMCMD_H
#define WORMS_TALLER_1_MOVECAMCMD_H


#include "Command.h"

class MoveCamCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_MOVECAMCMD_H
