//
// Created by abraham on 31/10/23.
//

#ifndef WORMS_TALLER_1_PLAYERS_H
#define WORMS_TALLER_1_PLAYERS_H


#include <map>
#include <vector>
#include "box2d/b2_world.h"
#include "Player.h"
#include "../../../../Common/DTO/PlayerDTO.h"
#include "../../../../Common/DTO/PlayersDTO.h"
#include "../../../../Common/DTO/WeaponsDTO.h"

class Players {
private:
    std::map<size_t, std::pair<float, float>> idsAndPositionsWorms;
    std::map<size_t, Player> players;
    size_t idCurrenPlayer;
    std::map<size_t, Player>::iterator playerIterator;
    const GameParameters& gameParameters;

public:
    explicit Players(const std::map<size_t, std::pair<float, float>> &idsAndPositionsWorms, const GameParameters& parameters);

    void addPlayer(const std::string &playerName, const size_t &idPlayer);

    void assignWormsToPlayers();

    std::vector<WormDTO> getWormsDTO() const;

    size_t getCurrentPlayerId();

    void addToTheWorld(b2World *world);

    std::pair<size_t, size_t> getIdPlayerWormCurrent();

    void updateStateWorms();

    PlayersDTO getPlayersDTO() const;

    std::vector<WeaponsDTO> getVecWeaponsDTO() const;

    Worm *getCurrentWorm();
};


#endif //WORMS_TALLER_1_PLAYERS_H
