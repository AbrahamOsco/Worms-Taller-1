//
// Created by riclui on 21/11/23.
//

#ifndef WORMS_TALLER_1_SELECTDYNAMITECMD_H
#define WORMS_TALLER_1_SELECTDYNAMITECMD_H


#include "Command.h"

class SelectDynamiteCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_SELECTDYNAMITECMD_H
