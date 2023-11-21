//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "ProjectileBazooka.h"
#include "../QueriesToWorld/SaveWormsInAreaQuery.h"
#include "../Worm/Worm.h"

ProjectileBazooka::ProjectileBazooka(const GameParameters& gameParameters, const TypeFocus& typeFocus) : GameObject(ENTITY_BAZOOKA_PROJECTILE) , gameParameters(gameParameters),
            explodable(gameParameters.getBazookaProjectileDamageMax(), gameParameters.getBazookProjectileRadio(), gameParameters.getBazookProjectileRadio() ){
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

    // aplicamos el efecto del viento LUEGO DE CREAR EL FIXTURE OJO.
    float windValueSelect = windValue/ this->body->GetMass();
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true); // Aplicamos el vector del viento en todo momento al projectil de la bazooka

    body->ApplyLinearImpulse( impulseProjectile, body->GetWorldCenter(), true);
    this->aWorld = aWorld;
}

ProjectileDTO ProjectileBazooka::getProjectilDTO(){
    return ProjectileDTO(BAZOOKA_PROJECTILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus);
}

void ProjectileBazooka::searchWormAndCollide(const b2Vec2 &projectilePosition){
    explodable.searchWormAndCollide(projectilePosition, aWorld);
    this->destroyBody();
}
