//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_SELECTAIRATTACKCMD_H
#define WORMS_TALLER_1_SELECTAIRATTACKCMD_H


#include "Command.h"

class SelectAirAttackCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SELECTAIRATTACKCMD_H
