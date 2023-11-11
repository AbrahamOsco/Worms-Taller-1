//
// Created by riclui on 11/11/23.
//

#ifndef WORMS_TALLER_1_SELECTTELEPORTCMD_H
#define WORMS_TALLER_1_SELECTTELEPORTCMD_H


#include "Command.h"

class SelectTeleportCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SELECTTELEPORTCMD_H
