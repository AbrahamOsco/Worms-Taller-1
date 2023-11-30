//
// Created by abraham on 26/10/23.
//

#ifndef WORMS_TALLER_1_PLAYER_H
#define WORMS_TALLER_1_PLAYER_H

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "box2d/b2_world.h"
#include <memory>
#include "../../../../Common/DTO/PlayerDTO.h"
#include "../../../GameParameters/GameParameters.h"
#include "../../../../Common/DTO/WeaponsDTO.h"
#include "../Weapons/Armament/Armament.h"
#include "../Worm/Worm.h"
#include "../../../../Common/DTO/EndGameDTO.h"

#define VALUE_INITIAL 1000

class Player {
 private:
    std::string playerName;
    size_t idPlayer;
    std::map<size_t, std::unique_ptr<Worm>> worms;
    std::map<size_t, std::unique_ptr<Worm>>::iterator wormIterator;
    size_t idCurrentWorm;
    const GameParameters& gameParameters;
    Armament armament;

 public:
    Player(const std::string& playerName, const size_t& idPlayer, const GameParameters& gameParameters);

    std::vector<WormDTO> getWormsDTO() const;

    WeaponsDTO getWeaponsDTO() const;

    size_t startAWormTurn();

    void assignWorm(const int &idWorm, const std::pair<float, float> &positionInitialWorm);

    void assignBonusLife();

    void addToTheWorld(b2World *world);

    void update();

    PlayerDTO getPlayerDTO(const size_t &idCurrentPlayer) const;

    Worm *getCurrentWorm();

    bool allWormsAreUnmoveAndNotExistsProjectiles();

    std::string getPlayerName() const;

    void endTurn();

    void execute(std::unique_ptr<CommandDTO> &aCommandDTO, const int &timeLeft);

    bool lostAllWorms();

    void assignWindValue(const float &aWindValue);

    EndGameDTO getEndGameDTO();

    void setLifeAllWorm(const float &aNewHP);

    void getMovingWorms(std::vector<std::pair<size_t, size_t>> &idPlayerAndWorm);

    std::unique_ptr<Worm> * getWorm(const size_t &idWorm);

    void disableAllFocus();
};


#endif  // WORMS_TALLER_1_PLAYER_H
