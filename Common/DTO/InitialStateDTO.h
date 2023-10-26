//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_INITIALSTATEDTO_H
#define WORMS_TALLER_1_INITIALSTATEDTO_H


#include <string>
#include "DTO.h"

class InitialStateDTO : public DTO {
private:
    std::string playerName;

public:
    InitialStateDTO();

    void setPlayerName(const std::string& aPlayerName);

    std::string getPlayerName() const;
};


#endif //WORMS_TALLER_1_INITIALSTATEDTO_H
