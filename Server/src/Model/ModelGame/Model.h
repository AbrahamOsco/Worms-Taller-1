//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_MODEL_H
#define WORMS_TALLER_1_MODEL_H

#include <cstddef>
#include "../Players/Player.h"
#include "../Scenario/Stage/Stage.h"
#include "../Players/Players.h"
#include "../../../../Common/DTO/PlayerDTO.h"
#include "../../../../Common/DTO/PlayersDTO.h"
#include "../../../../Common/DTO/CommandDTO.h"
#include "../../../../Common/DTO/WeaponsDTO.h"
#include <map>
#include <string>
#include "box2d/box2d.h"
#include "../GameContactListener/GameContactListener.h"
#include "../Turns/Turns.h"
#include <memory>
#include <vector>

class Model {
 private:
    size_t numberPlayerReq;
    size_t currentPlayers;
    bool finishedGame;
    Stage stage;
    Players players;
    b2World& world;
    GameContactListener gameContactListener;
    Turns turns;

 public:
    Model(const std::string &scenarioName, b2World &aWorld, GameParameters& parameters);

    void addPlayer(const std::string &playerName, const size_t &idPlayer);

    std::vector<WormDTO> getWormsDTO() const;

    StageDTO getStageDTO() const;

    PlayersDTO getPlayersDTO() const;

    std::vector<WeaponsDTO> getVecWeaponsDTO() const;

    StageDTO startAndGetStageDTO();

    void execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft);

    void update();

    WeaponSightDTO getWeaponSightDTO();

    ProjectilesDTO getProjectilesDTO();

    void subtractTime();

    TurnDTO getTurnDTO() const;

    void tryAttackVariablePower();

    int getTimeLeft() const;

    bool onlyOnePlayerExits();

    std::vector<EndGameDTO> getVecEndGameDTO();

    std::vector<ProvisionDTO> getVecProvisionDTO();

    void tryToChangeFocus();
};


#endif  // WORMS_TALLER_1_MODEL_H
