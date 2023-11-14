//
// Created by riclui on 13/11/23.
//

#ifndef WORMS_TALLER_1_CROSSHAIR_H
#define WORMS_TALLER_1_CROSSHAIR_H


#include "../GameObject.h"
#include "../../animation/Animation.h"

class Crosshair : public GameObject {
    TypeSight m_typeSight;
    Animation m_animation;

public:
    Crosshair(int x, int y, const TypeSight &typeSight);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override;

};


#endif //WORMS_TALLER_1_CROSSHAIR_H
