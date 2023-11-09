//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_PLAYERINFO_H
#define WORMS_TALLER_1_PLAYERINFO_H


#include <string>
#include "../GameObject.h"

class PlayerInfo : public GameObject {
private:
    int m_id;
    std::string m_name;
    int m_totalLife;
public:
    PlayerInfo(int id, const std::string &name, int totalLife);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override {}

    void setParams(int x, int y);

    int getHeight();
};


#endif //WORMS_TALLER_1_PLAYERINFO_H
