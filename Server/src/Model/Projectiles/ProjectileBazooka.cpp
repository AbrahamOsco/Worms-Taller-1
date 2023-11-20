//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "ProjectileBazooka.h"

ProjectileBazooka::ProjectileBazooka(const GameParameters& gameParameters, const TypeFocus& typeFocus) : GameObject(ENTITY_BAZOOKA_PROJECTILE) , gameParameters(gameParameters) {
    this->mainDamage = gameParameters.getBazookaProjectileDamageMax();
    this->radio = gameParameters.getBazookProjectileRadio();
    this->maxImpulseExplosion = gameParameters.getBazookaProjectilMaxImpulseExplosion();
    this->typeFocus = typeFocus;
}


b2AABB ProjectileBazooka::getAreaForSearch(const b2Vec2 &positionMunition) const {
    b2AABB searchArea;
    searchArea.lowerBound = positionMunition - b2Vec2(radio, radio);
    searchArea.upperBound = positionMunition + b2Vec2(radio, radio);
    return searchArea;
}

void
ProjectileBazooka::addToTheWorld(b2World *aWorld, b2Vec2 positionP2, const b2Vec2 &impulseProjectile, const float &windValue) {
    b2BodyDef projBazoDef;
    projBazoDef.type = b2_dynamicBody;
    projBazoDef.fixedRotation = true;
    projBazoDef.bullet = true;
    projBazoDef.position.Set(positionP2.x, positionP2.y );
    projBazoDef.userData.pointer = (uintptr_t) this;
    this->body = aWorld->CreateBody(&projBazoDef);
    b2CircleShape projBazoShape;
    projBazoShape.m_p.Set(0.0f, 0.0f); // offset de la posicion inicial va en (0,1) e 1 por q el radio de 1m empuja en 1 al origen de la circuferencia.
    projBazoShape.m_radius = 0.1f;

    b2FixtureDef defFixMuniBazooka;
    defFixMuniBazooka.shape = &projBazoShape;
    defFixMuniBazooka.density = 1.0f; // ver el tema del aire luego.
    this->body->CreateFixture(&defFixMuniBazooka);
    float windValueSelect = windValue/ this->body->GetMass();
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true); // Aplicamos el vector del viento en todo momento al projectil de la bazooka
    body->ApplyLinearImpulse( impulseProjectile, body->GetWorldCenter(), true);
    this->aWorld = aWorld;
}
b2World* ProjectileBazooka::getWorld(){
    return this->aWorld;
}

b2Vec2 ProjectileBazooka::getImpulseForWorm(const b2Vec2 &positionWorm, const b2Vec2 &positionProjectile,
                                            const float &distanceWormToProjectile) {
    b2Vec2 impulseDirection = positionWorm - positionProjectile;
    impulseDirection.Normalize();
    std::cout << "distanceWormToProjectile :" << distanceWormToProjectile << "\n";
    float impulseMagnitude = maxImpulseExplosion * std::max(0.0f, 1.0f - sqrt(distanceWormToProjectile) / radio );
    b2Vec2 impulseWorm = impulseMagnitude * impulseDirection;
    if(impulseDirection.x == 0){ // Si la normal en x es cero hizo un tiro a -90º sale volando para arriba.
        impulseWorm.y = maxImpulseExplosion;
    }
    return impulseWorm;
}

float ProjectileBazooka::getDamageForWorm(const float &wormDistanceSquared) {
    float factorDamage = 1.0f - sqrt(wormDistanceSquared) / radio;
    std::cout << "wormDistanceSquared: " << wormDistanceSquared <<  "factorDamage: " << factorDamage << "\n";
    float damageForWorm = mainDamage * std::max(0.0f, factorDamage);
    std::cout << "damageForWorm: " << damageForWorm << "\n";
    return damageForWorm;
}

ProjectileDTO ProjectileBazooka::getProjectilDTO(){
    return ProjectileDTO(BAZOOKA_PROJECTILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() -this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(), this->typeFocus);

}

