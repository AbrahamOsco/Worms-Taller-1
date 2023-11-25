//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "WeaponSight.h"
#include "../../../../GameParameters/GameParameters.h"
#define MAX_ANGLE 90.1

WeaponSight::WeaponSight(const float &rayLength, const float &rayAngle, const GameParameters& parameters)
        : rayLength(rayLength), rayAngle(rayAngle), gameParameters(parameters) {
}

void WeaponSight::resetRayCast(){
    this->weaponRayCast.resetRayCast();
}

void WeaponSight::increaseAngle() {
    rayAngle += 1.0f;
    if(rayAngle > MAX_ANGLE){
        rayAngle -= 1.0f;
    }
    //std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
}

void WeaponSight::decreaseAngle() {
    rayAngle -= 1.0f;
    if (rayAngle < -MAX_ANGLE){
        rayAngle += 1.0f;
    }
    //std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
}

GameObject* WeaponSight::getBodyCollidesWithRayCast(b2World *world, const b2Vec2& positionWorm, const Direction &directionCurrent) {
    b2Vec2 p1 = positionWorm;
    int factor = 1;
    this->direction = directionCurrent;
    if (this->direction == LEFT) factor = -1;
    b2Vec2 p2 = p1 + rayLength * b2Vec2(factor* cosf(rayAngle * DEGRATORADIANS), sinf(rayAngle * DEGRATORADIANS));
    world->RayCast(&weaponRayCast, p1, p2);
    if ( weaponRayCast.getFraction() <= 0.001f ){
        return nullptr;
    }

    GameObject* gameObject = (GameObject*) weaponRayCast.getBody()->GetUserData().pointer;
    if ( gameObject != nullptr and gameObject->getEntityType() == ENTITY_WORM){
        return gameObject;
    }
    return nullptr;
}


b2Vec2 WeaponSight::getPositionP2RayCast(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    b2Vec2 p1 = positionWorm;
    int factor = 1;
    this->direction = directionCurrent;
    if( direction == LEFT) {
        factor = -1;
    }
    b2Vec2 p2 = p1 + rayLength * b2Vec2( factor * cosf(rayAngle * DEGRATORADIANS), sinf(rayAngle * DEGRATORADIANS));
    return p2;
}


b2Vec2 WeaponSight::getImpulseForProjectil(const Direction& directionCurrent, std::pair<float, float> impulse){
    int factor = 1, factorAngle = 1;
    this->direction = directionCurrent;
    if ( direction == LEFT){
        factor = -1;
    }
    if (rayAngle < 0.0f){
        factorAngle = -1;
    }
    return b2Vec2(factor * impulse.first , impulse.second * factorAngle);
}

WeaponSightDTO WeaponSight::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    b2Vec2 p2 = getPositionP2RayCast(positionWorm, directionCurrent);
    return WeaponSightDTO(SHOW_SIGHT, p2.x * gameParameters.getPositionAdjustment() , gameParameters.getMaxHeightPixel() - p2.y* gameParameters.getPositionAdjustment());
}



