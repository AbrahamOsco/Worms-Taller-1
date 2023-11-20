//
// Created by riclui on 20/11/23.
//

#ifndef WORMS_TALLER_1_AIRATTACKCMD_H
#define WORMS_TALLER_1_AIRATTACKCMD_H


#include "Command.h"

class AirAttackCmd : public Command{
private:
    int m_x;
    int m_y;
public:
    AirAttackCmd(int x, int y);
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_AIRATTACKCMD_H
