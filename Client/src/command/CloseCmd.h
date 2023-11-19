//
// Created by riclui on 19/11/23.
//

#ifndef WORMS_TALLER_1_CLOSECMD_H
#define WORMS_TALLER_1_CLOSECMD_H


#include "Command.h"

class CloseCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_CLOSECMD_H
