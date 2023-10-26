//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_RESPONSEINITIALSTATEDTO_H
#define WORMS_TALLER_1_RESPONSEINITIALSTATEDTO_H


#include <string>
#include "DTO.h"

class ResponseInitialStateDTO : public DTO {
private:
    std::string gameName;
    std::string scenarioName;
    size_t playersRequired;
public:
    ResponseInitialStateDTO();

    void setGameName(const std::string& aGameName);

    void setScenarioName(const std::string& aScenarioName);

    void setPlayerRequired(const size_t& aPlayersRequired);

    std::string getGameName() const;

    std::string getScenarioName() const;

    size_t getPlayerRequired() const;


};


#endif //WORMS_TALLER_1_RESPONSEINITIALSTATEDTO_H
