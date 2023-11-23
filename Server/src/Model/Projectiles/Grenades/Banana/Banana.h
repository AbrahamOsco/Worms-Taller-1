//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_BANANA_H
#define WORMS_TALLER_1_BANANA_H


#include "../Grenade/Grenade.h"
#include "../../Explodable/Explodable.h"

class Banana : public Grenade {
private:
    TypeFocus typeFocus;
    Explodable explodable;
public:

    Banana(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus);

    ProjectileDTO getProjectilDTO() override;

    // para la dynamite
    void passTime() override;

    void explode();

    ~Banana() = default;
};


#endif //WORMS_TALLER_1_BANANA_H
