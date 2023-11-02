//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_MODEL_H
#define WORMS_TALLER_1_MODEL_H

#include <cstddef>
#include "Player.h"
#include "Stage.h"
#include "Players.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include <map>
#include <string>

class Model {
private:
    size_t numberPlayerReq;
    size_t currentPlayers;
    bool finishedGame;
    Players players;
    Stage stage;
public:
    Model(const std::string& scenarioName);

    void addPlayer(const std::string &playerName, const size_t &idPlayer);

    std::vector<PlayerDTO> getPlayersDTO() const;

    StageDTO getStageDTO() const;
};


#endif //WORMS_TALLER_1_MODEL_H
