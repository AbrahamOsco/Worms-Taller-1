//
// Created by riclui on 13/11/23.
//

#ifndef WORMS_TALLER_1_FIRECMD_H
#define WORMS_TALLER_1_FIRECMD_H


#include "Command.h"

class FireCmd  : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_FIRECMD_H
