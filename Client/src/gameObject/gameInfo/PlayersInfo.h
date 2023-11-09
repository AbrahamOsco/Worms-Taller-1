//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_PLAYERSINFO_H
#define WORMS_TALLER_1_PLAYERSINFO_H


#include "PlayerInfo.h"

class PlayersInfo : public GameObject {
private:
    std::vector<PlayerInfo> m_players;
public:
    PlayersInfo();

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override {}

    void addPlayer(PlayerInfo &player);

    void verticalAligned(int verticalSpacing);
};


#endif //WORMS_TALLER_1_PLAYERSINFO_H