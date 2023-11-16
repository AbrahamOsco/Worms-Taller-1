//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_GAMEINFO_H
#define WORMS_TALLER_1_GAMEINFO_H


#include "../GameObject.h"
#include "PlayerInfo.h"
#include "WeaponInventory.h"
#include "WindInfo.h"
#include "PlayersInfo.h"

class GameInfo : public GameObject {
private:
    PlayersInfo m_players;
    WeaponInventory m_weaponInventory;
    WindInfo m_wind;
    std::string m_currentTurn;
    int m_time;
    bool m_isMyTurn;
public:
    GameInfo(PlayersInfo &players, WeaponInventory &weaponInventory, WindInfo &wind,
             const std::string &currentTurn, int time);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override;
};


#endif //WORMS_TALLER_1_GAMEINFO_H
