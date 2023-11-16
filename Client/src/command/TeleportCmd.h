//
// Created by riclui on 16/11/23.
//

#ifndef WORMS_TALLER_1_TELEPORTCMD_H
#define WORMS_TALLER_1_TELEPORTCMD_H


#include "Command.h"

class TeleportCmd : public Command {
private:
    int m_x;
    int m_y;
public:
    TeleportCmd(int x, int y);
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_TELEPORTCMD_H
