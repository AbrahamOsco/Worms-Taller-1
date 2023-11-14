//
// Created by riclui on 14/11/23.
//

#ifndef WORMS_TALLER_1_SELECTBAZOOKA_H
#define WORMS_TALLER_1_SELECTBAZOOKA_H


#include "Command.h"

class SelectBazooka : public Command {
public:
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_SELECTBAZOOKA_H
