//
// Created by riclui on 21/11/23.
//

#ifndef WORMS_TALLER_1_SELECTREDGRENADECMD_H
#define WORMS_TALLER_1_SELECTREDGRENADECMD_H


#include "Command.h"

class SelectRedGrenadeCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SELECTREDGRENADECMD_H
