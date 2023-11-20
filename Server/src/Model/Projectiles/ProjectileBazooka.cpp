//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "ProjectileBazooka.h"

ProjectileBazooka::ProjectileBazooka(const GameParameters& gameParameters, const TypeFocus& typeFocus) : GameObject(ENTITY_BAZOOKA_PROJECTILE) , gameParameters(gameParameters) {
    this->mainDamage = gameParameters.getBazookaProjectileDamageMax();
    this->maxRadio = gameParameters.getBazookProjectileRadio();
    this->maxImpulseMagnitude = gameParameters.getBazookaProjectilMaxImpulseExplosion();
    this->typeFocus = typeFocus;
}

void ProjectileBazooka::addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile, const float &windValue) {
    b2BodyDef projBazoDef;
    projBazoDef.type = b2_dynamicBody;
    projBazoDef.fixedRotation = true;
    projBazoDef.bullet = true;
    projBazoDef.position.Set(positionP2.x, positionP2.y );
    projBazoDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&projBazoDef);
    b2CircleShape projBazoShape;
    projBazoShape.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el maxRadio de 1m empuja en 1 al origen de la circuferencia.
    projBazoShape.m_radius = 0.1f;

    b2FixtureDef defFixMuniBazooka;
    defFixMuniBazooka.shape = &projBazoShape;
    defFixMuniBazooka.density = 1.0f; // ver el tema del aire luego.
    this->body->CreateFixture(&defFixMuniBazooka);
    // aplicamos el efecto del viento.
    float windValueSelect = windValue/ this->body->GetMass();
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true); // Aplicamos el vector del viento en todo momento al projectil de la bazooka

    body->ApplyLinearImpulse( impulseProjectile, body->GetWorldCenter(), true);
    this->aWorld = aWorld;
}
b2World* ProjectileBazooka::getWorld(){
    return this->aWorld;
}

b2AABB ProjectileBazooka::getAreaForSearch(const b2Vec2 &positionProjectile) const {
    b2AABB searchArea;
    searchArea.lowerBound = positionProjectile - b2Vec2(maxRadio, maxRadio);
    searchArea.upperBound = positionProjectile + b2Vec2(maxRadio, maxRadio);
    return searchArea;
}

b2Vec2 ProjectileBazooka::getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
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

float ProjectileBazooka::getDamageForWorm(const float &wormDistanceSquared) {
    return mainDamage * std::max(0.0f, 1.0f - sqrt(wormDistanceSquared) / maxRadio);
}

ProjectileDTO ProjectileBazooka::getProjectilDTO(){
    return ProjectileDTO(AIR_ATTACK_MISSILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus);
}

