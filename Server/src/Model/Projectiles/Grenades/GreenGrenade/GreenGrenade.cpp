//
// Created by abraham on 22/11/23.
//

#include <iostream>
#include "GreenGrenade.h"
// Aca ponemos el danio main, radio y el impulso explosion.
GreenGrenade::GreenGrenade(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus) : Grenade(gameParameters, waitTime),
            typeFocus(typeFocus), explodable(40.0f, 2.0f, 3.0f) {
    // para configurar el tipo de granada. obligatorio responde.
    fixedRotation = true;
    restitution = 0.0f;
}

ProjectileDTO GreenGrenade::getProjectilDTO() {
    return ProjectileDTO(PROJ_GREEN_GRENADE, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
}

void GreenGrenade::passTime() {
    if (collided) {
        time = std::chrono::steady_clock::now();
        if (time - startTime >= waitTime && !exploded){
            explode();
        }
    }
}

void GreenGrenade::explode() {
    std::cout << "Se explota la green granada\n";
    this->exploded = true;
    explodable.searchWormAndCollide(body->GetWorldCenter(), world);
    this->destroyBody();
}


