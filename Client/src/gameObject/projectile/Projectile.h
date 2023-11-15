//
// Created by riclui on 14/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILE_H
#define WORMS_TALLER_1_PROJECTILE_H


#include "../GameObject.h"

class Projectile : public GameObject {
    TypeProjectil m_typeProjectile;

public:
    Projectile(int x, int y, const TypeProjectil &typeProjectile);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager) override;

    void update(float dt, Input &input, Queue<std::unique_ptr<Command>> &queue) override {}
};


#endif //WORMS_TALLER_1_PROJECTILE_H
