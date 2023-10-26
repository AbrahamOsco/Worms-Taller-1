//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_ROOMDTO_H
#define WORMS_TALLER_1_ROOMDTO_H


#include <string>
#include "DTO.h"

class RoomDTO : public DTO {
private:
    std::string gameName;
    std::string scenarioName;
    size_t playersCurrent;
    size_t playersRequired;
public:
    RoomDTO();

    RoomDTO(const std::string& aGameName, const std::string& aScenarioName, const size_t& aPlayerCurrent, const size_t& aPlayersRequired);

    void setGameName(const std::string& aGameName);

    void setScenarioName(const std::string& aScenarioName);

    void setPlayerRequired(const size_t& aPlayersRequired);

    void setPlayerCurent(const size_t& aPlayerCurrent);

    std::string getGameName() const;

    std::string getScenarioName() const;

    size_t getPlayerRequired() const;

    size_t getPlayerCurrent() const;

};


#endif //WORMS_TALLER_1_ROOMDTO_H
