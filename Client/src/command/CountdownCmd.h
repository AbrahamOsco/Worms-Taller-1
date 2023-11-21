//
// Created by riclui on 21/11/23.
//

#ifndef WORMS_TALLER_1_COUNTDOWNCMD_H
#define WORMS_TALLER_1_COUNTDOWNCMD_H


#include "Command.h"

class CountdownCmd : public Command {
private:
    int m_count;

public:
    CountdownCmd(int count);
    void execute(ClientProtocol &protocol) override;
};


#endif //WORMS_TALLER_1_COUNTDOWNCMD_H
