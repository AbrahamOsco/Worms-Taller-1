//
// Created by riclui on 18/11/23.
//

#ifndef WORMS_TALLER_1_WORMRANGEDWEAPON_H
#define WORMS_TALLER_1_WORMRANGEDWEAPON_H

#include "Worm.h"
#include "../crosshair/Crosshair.h"

class WormRangedWeapon : public Worm {
    TypeWeapon m_weaponCurrent;
    Crosshair m_crossHair;
    int m_xCrossHair;
    int m_yCrossHair;
public:
    WormRangedWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocus &focus,
                     const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrossHair, int yCrossHair,
                     const TypeSight &typeSight);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;

    int calculateAngle(int x, int y, Direction direction) const;
};


#endif //WORMS_TALLER_1_WORMRANGEDWEAPON_H
