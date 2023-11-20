//
// Created by abraham on 20/11/23.
//

#include <iostream>
#include "AirAttackMissile.h"

AirAttackMissile::AirAttackMissile(const GameParameters &gameParameters, const TypeFocus& typeFocus) : GameObject(ENTITY_AIR_ATTACK_MISSILE),
                    gameParameters(gameParameters), typeFocus(typeFocus){

}

void AirAttackMissile::addToTheWorld(b2World *aWorld, const b2Vec2 &positionMissile, const float &windValue) {
    b2BodyDef airAttackMissileDef;
    airAttackMissileDef.type = b2_dynamicBody;
    airAttackMissileDef.fixedRotation = true;
    airAttackMissileDef.position.Set(positionMissile.x, positionMissile.y );
    airAttackMissileDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&airAttackMissileDef);
    b2CircleShape airAttackMissileForm;
    airAttackMissileForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el maxRadio de 1m empuja en 1 al origen de la circuferencia..
    airAttackMissileForm.m_radius = 0.1f;
    b2FixtureDef defFixAirAttackMis;
    defFixAirAttackMis.shape = &airAttackMissileForm;
    defFixAirAttackMis.density = 1.0f; // ver el tema del aire luego.

    // aplicamos el efecto del viento.
    float windValueSelect = windValue/ this->body->GetMass();
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true); // Aplicamos el vector del viento en todo momento al projectil de la bazooka

    this->body->CreateFixture(&defFixAirAttackMis);
    this->aWorld = aWorld;
}
// todos los metodos de abajo en un futuro pasarlo a una clase y delegar directamente a esa clase.
b2AABB AirAttackMissile::getAreaForSearch(const b2Vec2& positionMissile) const {
    b2AABB searchArea;
    searchArea.lowerBound = positionMissile - b2Vec2(2.0f, 2.0f);
    searchArea.upperBound = positionMissile + b2Vec2(2.0f, 2.0f);
    return searchArea;
}


b2Vec2 AirAttackMissile::getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                                            const float &distanceWormToProjectile) {
    b2Vec2 impulseDirection = positionWorm - positionProjectile;
    impulseDirection.Normalize();
    float impulseMagnitude = maxImpulseMagnitude * std::max(0.0f, 1.0f - sqrt(distanceWormToProjectile) / maxRadio );
    b2Vec2 impulseWorm = impulseMagnitude * impulseDirection;
    if(impulseDirection.x == 0){ // Si la normal en x es cero hizo un tiro a -90º sale volando para arriba.
        impulseWorm.y = maxImpulseMagnitude;
    }
    return impulseWorm;
}

float AirAttackMissile::getDamageForWorm(const float &wormDistanceSquared) {
    return mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistanceSquared) / maxRadio);
}

ProjectileDTO AirAttackMissile::getProjectilDTO(){
    return ProjectileDTO(AIR_ATTACK_MISSILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() -this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(), this->typeFocus);
}

b2World* AirAttackMissile::getWorld(){
    return this->aWorld;
}
