//
// Created by riclui on 18/11/23.
//

#ifndef WORMS_TALLER_1_WORMNOWEAPON_H
#define WORMS_TALLER_1_WORMNOWEAPON_H

#include "Worm.h"

class WormNoWeapon : public Worm {
public:
    WormNoWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus, const MoveWorm &moveWorm);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) override;

};


#endif //WORMS_TALLER_1_WORMNOWEAPON_H
