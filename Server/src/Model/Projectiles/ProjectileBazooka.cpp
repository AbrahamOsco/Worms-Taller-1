//
// Created by abraham on 13/11/23.
//

#include "ProjectileBazooka.h"

ProjectileBazooka::ProjectileBazooka(const GameParameters& gameParameters) : GameObject(ENTITY_BAZOOKA_PROJECTILE) , gameParameters(gameParameters) {
}

b2AABB ProjectileBazooka::getAreaForSearch(const b2Vec2 &positionMunition) const {
    b2AABB searchArea;
    searchArea.lowerBound = positionMunition - b2Vec2(2.0f, 2.0f);
    searchArea.upperBound = positionMunition + b2Vec2(2.0f, 2.0f);
    return searchArea;
}

void ProjectileBazooka::addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile) {
    b2BodyDef munitBazoDef;
    munitBazoDef.type = b2_dynamicBody;
    munitBazoDef.fixedRotation = true;
    munitBazoDef.position.Set(positionP2.x, positionP2.y );
    munitBazoDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&munitBazoDef);
    b2CircleShape munitBazoForm;
    munitBazoForm.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia..
    munitBazoForm.m_radius = 0.1f;

    b2FixtureDef defFixMuniBazooka;
    defFixMuniBazooka.shape = &munitBazoForm;
    defFixMuniBazooka.density = 1.0f; // ver el tema del aire luego.
    this->body->CreateFixture(&defFixMuniBazooka);
    body->ApplyLinearImpulse( impulseProjectile, body->GetWorldCenter(), true);
}

b2Vec2 ProjectileBazooka::getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                                            const float &distanceWormToProjectile) {
    b2Vec2 impulseDirection = positionWorm - positionProjectile;
    impulseDirection.Normalize();
    float impulseMagnitude = maxImpulseExplosion * std::max(0.0f, 1.0f - sqrt(distanceWormToProjectile) / radio );
    b2Vec2 impulseWorm = impulseMagnitude * impulseDirection;
    //impulseWorm.y = abs(impulseWorm.x) * 0.7;  // todo seguramnte falta ajustar aca el eje y
    return impulseWorm;
}

float ProjectileBazooka::getDamageForWorm(const float &wormDistanceSquared) {
    float damageForWorm = mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistanceSquared) / radio);
    return damageForWorm;
}



