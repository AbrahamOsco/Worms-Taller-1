//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONSIGHT_H
#define WORMS_TALLER_1_WEAPONSIGHT_H


#include "../WeaponRayCast/WeaponRayCast.h"
#include "../../../../../Common/DTO/WormDTO.h"
#include "../../../../../Common/DTO/WeaponSightDTO.h"
#include "../../../../GameParameters/GameParameters.h"
#include "../../GameObject/GameObject.h"

#define DEGRATORADIANS (b2_pi/180.0f)
#define RADIANSTODEGREE (180/b2_pi)

class WeaponSight {
private:
    WeaponRayCast weaponRayCast;
    float rayLength;
    float rayAngle; // esta en grados.
    Direction direction; //posiblemnte elminarla ya que lo usamos dentro de un metodo y como que no mas por ej ataques
    const GameParameters& gameParameters;
public:
    WeaponSight(const float &rayLength, const float &rayAngle, const GameParameters& parameters);

    void resetRayCast();

    void increaseAngle();

    void decreaseAngle();

    GameObject *getBodyCollidesWithRayCast(b2World *world, const b2Vec2 &positionWorm, const Direction &directionCurrent);

    b2Vec2 getPositionP2RayCast(const b2Vec2 &positionWorm, const Direction &directionCurrent);

    WeaponSightDTO getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent);

    b2Vec2 getImpulseForProjectil(const Direction &directionCurrent, std::pair<float, float> impulse);
};


#endif //WORMS_TALLER_1_WEAPONSIGHT_H
