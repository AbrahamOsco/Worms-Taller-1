//
// Created by riclui on 19/11/23.
//

#ifndef WORMS_TALLER_1_WORMGUIDEDWEAPON_H
#define WORMS_TALLER_1_WORMGUIDEDWEAPON_H


#include "Worm.h"

class WormGuidedWeapon : public Worm {
private:
    TypeWeapon m_weaponCurrent;

public:
    WormGuidedWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocus &focus,
                     const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif //WORMS_TALLER_1_WORMGUIDEDWEAPON_H
