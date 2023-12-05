//
// Created by abraham on 20/11/23.
//

#include <iostream>
#include "AirAttackMissile.h"

// @todo falta borrar numeros magicos aca
AirAttackMissile::AirAttackMissile(const GameParameters &gameParameters, const TypeFocus& typeFocus) :
                GameObject(ENTITY_AIR_ATTACK_MISSILE), gameParameters(gameParameters), typeFocus(typeFocus),
                explodable(gameParameters.airAttackMissileGetDamage(), gameParameters.airAttackMissleGetMaxRadio(),
                gameParameters.airAttackMissileImpulseMax() ), aWorld(nullptr) {
    explosionIterations = gameParameters.getAnimationIterations();
}

void AirAttackMissile::addToTheWorld(b2World *aWorld, const b2Vec2 &positionMissile, const float &windValue) {
    b2BodyDef airAttackMissileDef;
    airAttackMissileDef.type = b2_dynamicBody;
    airAttackMissileDef.fixedRotation = true;
    airAttackMissileDef.position.Set(positionMissile.x, positionMissile.y);
    airAttackMissileDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&airAttackMissileDef);
    b2CircleShape airAttackMissileForm;
    airAttackMissileForm.m_p.Set(0.0f, 0.0f);
    airAttackMissileForm.m_radius = 0.1f;
    b2FixtureDef defFixAirAttackMis;
    defFixAirAttackMis.shape = &airAttackMissileForm;
    defFixAirAttackMis.density = 1.0f;
    this->body->CreateFixture(&defFixAirAttackMis);
    float windValueSelect = (windValue/ this->body->GetMass());
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true);
    this->aWorld = aWorld;
    explosionIterations = gameParameters.getAnimationIterations();
}

void AirAttackMissile::searchWormAndCollide(const b2Vec2 &projectilePosition) {
    explodable.searchWormAndCollide(projectilePosition, aWorld);
    this->destroyBody();
}

ProjectileDTO AirAttackMissile::getProjectilDTO() {
    return ProjectileDTO(AIR_ATTACK_MISSILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
            gameParameters.getMaxHeightPixel() -this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(),
            this->typeFocus, NO_EXPLODE);
}

bool AirAttackMissile::hasExplosionIterations() const {
    return (explosionIterations > 0);
}

void AirAttackMissile::removeAIteration() {
    explosionIterations--;
}

int AirAttackMissile::getNumberIterations() const {
    return explosionIterations;
}



