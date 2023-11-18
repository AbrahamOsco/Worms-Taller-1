//
// Created by abraham on 09/11/23.
//

#include <iostream>
#include "Teleport.h"
#include "../../QueriesToWorld/PositionInAreaisFreeQuery.h"

Teleport::Teleport(const TypeWeapon &aTypeWeapon, const float &mainDamage, const TypeMunition &aTypeMunition,
                   const size_t &aMunition, const GameParameters& gameParameters) : Weapon(aTypeWeapon, mainDamage, aTypeMunition, aMunition, gameParameters) {

}
bool Teleport::isPositionFree(const b2Vec2& positionToTeleport, b2World* aWorld){
    PositionInAreaisFreeQuery positionInAreaisFreeQuery;
    b2AABB aabb;
    b2Vec2 delta = b2Vec2(0.0001f, 0.0001f); // Ajusta según sea necesario
    aabb.lowerBound = positionToTeleport - delta;
    aabb.upperBound = positionToTeleport + delta;
    aWorld->QueryAABB(&positionInAreaisFreeQuery, aabb);

    return positionInAreaisFreeQuery.getPositionIsFree();
}


void Teleport::teleportIn(b2Body *bodyWorm, const float &posXTeleportPix, const float &posYTeleportPix, b2World *aWorld) {
    float posXInMeters = posXTeleportPix / gameParameters.getPositionAdjustment();
    float posYInMeters = ((gameParameters.getMaxHeightPixel() - posYTeleportPix) / gameParameters.getPositionAdjustment()) - 0.6 ;
    // Si hay un objeto donde nos queremos teletransportar NO lo hacemos entonces.
    b2Vec2 positionToTp(posXInMeters, posYInMeters);
    if(not isPositionFree(positionToTp, aWorld) ){
        std::cout << "Hay un objeto Donde queres tepear.\n";
        return;
    }
    b2Vec2 aNewPosition = b2Vec2(posXInMeters, posYInMeters );
    bodyWorm->SetTransform(aNewPosition, 0);
    b2Vec2 smallImpulse(0.0f, -0.001f); // aplico pequeño impulso para despertar al objeto de su teleport.
    bodyWorm->ApplyLinearImpulse(smallImpulse, bodyWorm->GetWorldCenter(), true);
}

bool Teleport::hasAScope() {
    return false;
}

bool Teleport::launchesProjectiles() {
    return false;
}

bool Teleport::hasVariablePower() {
    return false;
}


