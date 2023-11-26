//
// Created by riclui on 18/11/23.
//

#ifndef WORMS_TALLER_1_WORMNOWEAPON_H
#define WORMS_TALLER_1_WORMNOWEAPON_H

#include <memory>
#include "Worm.h"
#include "../../soundManager/SoundManager.h"

class WormNoWeapon : public Worm {
 public:
    WormNoWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction,
                const TypeFocus &focus, const MoveWorm &moveWorm, bool isMyTurn);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif  // WORMS_TALLER_1_WORMNOWEAPON_H
