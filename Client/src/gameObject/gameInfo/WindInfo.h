//
// Created by riclui on 09/11/23.
//

#ifndef WORMS_TALLER_1_WINDINFO_H
#define WORMS_TALLER_1_WINDINFO_H


#include "../../../../Common/DTO/WormDTO.h"
#include "../GameObject.h"

class WindInfo : public GameObject {
private:
    int m_velocity;
    Direction m_direction;
public:
    WindInfo(int velocity, Direction direction);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override {}
};


#endif //WORMS_TALLER_1_WINDINFO_H
