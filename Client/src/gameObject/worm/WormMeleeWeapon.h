//
// Created by riclui on 19/11/23.
//

#ifndef WORMS_TALLER_1_WORMMELEEWEAPON_H
#define WORMS_TALLER_1_WORMMELEEWEAPON_H


#include "Worm.h"
#include "../crosshair/Crosshair.h"

class WormMeleeWeapon : public Worm {
private:
    TypeWeapon m_weaponCurrent;
    Crosshair m_crossHair;

public:
    WormMeleeWeapon(int id, int x, int y, const size_t &hpWorm, const Direction &direction, const TypeFocusWorm &focus, const MoveWorm &moveWorm, const TypeWeapon &weaponCurrent, int xCrossHair, int yCrossHair, const TypeSight &typeSight, bool isMyTurn);

    void draw(SDL2pp::Renderer &renderer, TextureManager &textureManager, Camera &camera) override;

    void
    update(Input &input, Queue<std::unique_ptr<Command>> &queue, Camera &camera, SoundManager &soundManager) override;
};


#endif //WORMS_TALLER_1_WORMMELEEWEAPON_H
