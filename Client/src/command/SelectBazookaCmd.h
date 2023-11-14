//
// Created by riclui on 14/11/23.
//

#ifndef WORMS_TALLER_1_SELECTBAZOOKACMD_H
#define WORMS_TALLER_1_SELECTBAZOOKACMD_H


#include "Command.h"

class SelectBazookaCmd : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SELECTBAZOOKACMD_H
