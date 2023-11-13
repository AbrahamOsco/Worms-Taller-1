//
// Created by abraham on 09/11/23.
//

#include "Teleport.h"

Teleport::Teleport(const TypeWeapon &aTypeWeapon, const float &damagePrincipal, const TypeMunition &aTypeMunition,
                   const size_t &aMunition, const GameParameters& gameParameters) : Weapon(aTypeWeapon, damagePrincipal, aTypeMunition, aMunition, gameParameters) {

}

void Teleport::teleportIn(b2Body* bodyWorm, const float& posXTeleport, const float& posYTeleport){
    b2Vec2 aNewPosition = b2Vec2(posXTeleport, posYTeleport);
    bodyWorm->SetTransform(aNewPosition, 0);
    b2Vec2 smallImpulse(0.0f, -0.001f); // aplico pequeño impulso para despertar al objeto de su teleport.
    bodyWorm->ApplyLinearImpulse(smallImpulse, bodyWorm->GetWorldCenter(), true);
}

bool Teleport::hasAScope() {
    return false;
}


