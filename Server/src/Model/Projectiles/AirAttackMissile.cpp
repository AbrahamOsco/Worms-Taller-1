//
// Created by abraham on 20/11/23.
//

#include <iostream>
#include "AirAttackMissile.h"

// @todo falta borrar numeros magicos aca
AirAttackMissile::AirAttackMissile(const GameParameters &gameParameters, const TypeFocus& typeFocus) : GameObject(ENTITY_AIR_ATTACK_MISSILE),
                    gameParameters(gameParameters), typeFocus(typeFocus), explodable( 40.0, 2.0f, 2.0f ){

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

    this->body->CreateFixture(&defFixAirAttackMis); // Inmediatamente luego de ajustar los fixture crearlo en el cuerpo sino no tendra masa hasta ahora el cuerpo MUY Impotante.
    float windValueSelect = (windValue/ this->body->GetMass());
    b2Vec2 vectorWind(windValueSelect, 0.0f);
    this->body->ApplyForceToCenter(vectorWind, true); // Aplicamos el vector del viento en todo momento al projectil de la bazooka
    this->aWorld = aWorld;
}


void AirAttackMissile::searchWormAndCollide(const b2Vec2 &projectilePosition){
    explodable.searchWormAndCollide(projectilePosition, aWorld);
    this->destroyBody();
}


ProjectileDTO AirAttackMissile::getProjectilDTO(){
    return ProjectileDTO(AIR_ATTACK_MISSILE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() -this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment(), this->typeFocus);
}
