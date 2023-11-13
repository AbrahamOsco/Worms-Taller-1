//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "WeaponSight.h"
#include "GameObject.h"
#include "../../GameParameters/GameParameters.h"

WeaponSight::WeaponSight(const float &rayLength, const float &rayAngle, const GameParameters& parameters)
        : rayLength(rayLength), rayAngle(rayAngle), gameParameters(parameters) {
}

void WeaponSight::resetRayCast(){
    this->weaponRayCast.resetRayCast();
}

void WeaponSight::increaseAngle() {
    rayAngle += 10.0f;
    if(rayAngle > 90.1f){
        rayAngle -= 10.0f;
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
}

void WeaponSight::decreaseAngle() {
    rayAngle -= 10.0f;
    if (rayAngle < -90.1f){
        rayAngle += 10.0f;
    }
    std::cout << "Angle current Degree / Rad: : " << rayAngle << " / " <<  rayAngle * DEGRATORADIANS << " \n";
}

GameObject* WeaponSight::getBodyCollidesWithRayCast(b2World *world, const b2Vec2& positionWorm, const Direction &directionCurrent) {
    b2Vec2 p1 = positionWorm;
    int factor = 1;
    this->direction = directionCurrent;
    if (this->direction == LEFT) factor = -1;
    b2Vec2 p2 = p1 + rayLength * b2Vec2(factor* cosf(rayAngle * DEGRATORADIANS), sinf(rayAngle * DEGRATORADIANS));
    world->RayCast(&weaponRayCast, p1, p2);
    std::cout << "weaponRayCast->getFraction(): " << weaponRayCast.getFraction() << "\n";
    if ( weaponRayCast.getFraction() <= 0.001f ){
        std::cout << "Practicamente no colisione con nada ni recorri el 1% de la trayectoria asi que salgo\n";
        return nullptr;
    }

    GameObject* gameObject = (GameObject*) weaponRayCast.getBody()->GetUserData().pointer;
    if ( gameObject != nullptr and gameObject->getEntityType() == ENTITY_WORM){
        std::cout << "colisione con un gusano ahora le bajo la vida a punta de un golpe \n";
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
    std::cout << "Ray angle degr:" << rayAngle;
    std::cout << " |    p2.x : " << p2.x << " p2 .y : " << p2.y << " \n ";
    return p2;
}


b2Vec2 WeaponSight::getImpulseForMuniBazooka(const Direction& directionCurrent, std::pair<float, float> impulse){
    int factor = 1, factorAngle = 1;
    this->direction = directionCurrent;
    if ( direction == LEFT){
        factor = -1;
    }
    // este if solo para la bazooka porque hace mov parabolico el misil. para darle efecto parabolico cuando los angulos son negativos nada mas
    if (rayAngle < 0.0f){
        factorAngle = -1; // OK !
    }
    return b2Vec2(factor * impulse.first , impulse.second * factorAngle);
}

WeaponSightDTO WeaponSight::getWeaponSightDTO(const b2Vec2 &positionWorm, const Direction &directionCurrent) {
    b2Vec2 p2 = getPositionP2RayCast(positionWorm, directionCurrent);
    // todo falta agregar el 1080 - 60* p2.x  e 60 * p2.y
    return WeaponSightDTO(SHOW_SIGHT, p2.x * gameParameters.getPositionAdjustment() , gameParameters.getMaxHeightPixel() - p2.y* gameParameters.getPositionAdjustment());
}



