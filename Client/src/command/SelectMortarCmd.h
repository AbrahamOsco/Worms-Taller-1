//
// Created by riclui on 21/11/23.
//

#ifndef WORMS_TALLER_1_SELECTMORTARCMD_H
#define WORMS_TALLER_1_SELECTMORTARCMD_H


#include "Command.h"

class SelectMortarCmd : public Command {
 public:
    void execute(ClientProtocol &protocol) override;
};


#endif  // WORMS_TALLER_1_SELECTMORTARCMD_H
