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
    b2Vec2 delta = b2Vec2(0.01f, 0.01f); // Ajusta según sea necesario
    aabb.lowerBound = positionToTeleport - delta;
    aabb.upperBound = positionToTeleport + delta;
    aWorld->QueryAABB(&positionInAreaisFreeQuery, aabb);
    std::cout << "Área de consulta: (" << aabb.lowerBound.x << ", " << aabb.lowerBound.y << ") - (" << aabb.upperBound.x << ", " << aabb.upperBound.y << ")" << std::endl;
    return positionInAreaisFreeQuery.getPositionIsFree();
}


void Teleport::teleportIn(b2Body *bodyWorm, const int &posXPix, const int &posYPix, b2World *aWorld) {
    float posXInMeters =  (float) posXPix / gameParameters.getPositionAdjustment();
    float posYInMeters = ((gameParameters.getMaxHeightPixel() - ((float) posYPix)) / gameParameters.getPositionAdjustment());
    if(posYInMeters >= 17.5){
        return;
    }
    // Si hay un objeto donde nos queremos teletransportar NO lo hacemos entonces.
    b2Vec2 positionToTp(posXInMeters, posYInMeters);
    std::cout << "Posición en píxeles: " << posXPix << ", " << posYPix << std::endl;
    std::cout << "Posición en metros: " << posXInMeters << ", " << posYInMeters << std::endl;
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


