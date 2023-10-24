//
// Created by abraham on 24/10/23.
//

#ifndef WORMS_TALLER_1_LOBBYANSWERDTO_H
#define WORMS_TALLER_1_LOBBYANSWERDTO_H


#include <string>
#include "DTO.h"

class LobbyAnswerDTO : public DTO {
private:
    std::string gameName;
    std::string selectedScenario;

public:

    LobbyAnswerDTO();

    void setGameName(const std::string& aGameName);

    void setSelectScenario(const std::string& aSelectedScenario);

    std::string getGameName() const;

    std::string getSelectedScenario() const;
};


#endif //WORMS_TALLER_1_LOBBYANSWERDTO_H
