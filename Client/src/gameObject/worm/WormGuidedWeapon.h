//
// Created by riclui on 18/11/23.
//

#ifndef WORMS_TALLER_1_WORMGUIDEDWEAPON_H
#define WORMS_TALLER_1_WORMGUIDEDWEAPON_H

#include "Worm.h"

class WormGuidedWeapon : public Worm {
    TypeWeapon m_weaponCurrent;
    int m_xCrossHair;
    int m_yCrossHair;
    TypeSight m_typeSight;
public:
    WormGuidedWeapon(int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus,
                     const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrossHair, int yCrossHair,
                     const TypeSight &typeSight);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera) override;

    int calculateAngle(int x, int y, Direction direction) const;
};


#endif //WORMS_TALLER_1_WORMGUIDEDWEAPON_H
