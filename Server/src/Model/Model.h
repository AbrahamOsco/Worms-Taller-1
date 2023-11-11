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
#include "../../../Common/DTO/PlayersDTO.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../../../Common/DTO/WeaponsDTO.h"
#include <map>
#include <string>
#include <box2d/box2d.h>
#include <memory>

class Model {
private:
    size_t numberPlayerReq;
    size_t currentPlayers;
    bool finishedGame;
    Stage stage;
    Players players;
    b2World& world;
    std::pair<size_t, size_t> idPlayerWormCurrent;

public:

    Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters);

    void addPlayer(const std::string &playerName, const size_t &idPlayer);

    std::vector<WormDTO> getWormsDTO() const;

    StageDTO getStageDTO() const;

    PlayersDTO getPlayersDTO() const;

    std::vector<WeaponsDTO> getVecWeaponsDTO() const;

    void start();

    void execute(std::unique_ptr<CommandDTO> &aCommandDTO);

    void updateStateWorms();
};


#endif //WORMS_TALLER_1_MODEL_H
