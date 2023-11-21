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
#include "../../soundManager/SoundManager.h"

class GameInfo : public GameObject {
private:
    PlayersInfo m_players;
    WeaponInventory m_weaponInventory;
    WindInfo m_wind;
    std::string m_currentTurn;
    int m_time;
    bool m_isMyTurn;
    GameState m_gameState;
    TypeResult m_typeResult;
    bool m_deathWorm;

public:
    GameInfo(PlayersInfo &players, WeaponInventory &weaponInventory, WindInfo &wind, GameState &gameState, TypeResult &typeResult,
             const std::string &currentTurn, int time, bool deathWorm);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif //WORMS_TALLER_1_GAMEINFO_H
