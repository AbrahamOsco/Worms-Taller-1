//
// Created by abraham on 23/11/23.
//

#include <iostream>
#include "Banana.h"
Banana::Banana(const GameParameters &gameParameters, const int& waitTime, const TypeFocus& typeFocus) :
            Grenade(gameParameters, waitTime), typeFocus(typeFocus),  explodable(70.0f, 4.0f, 1.0f){

}

ProjectileDTO Banana::getProjectilDTO() {
    return ProjectileDTO(PROJ_BANANA, this->body->GetWorldCenter().x * gameParameters.getPositionAdjustment(),
                         gameParameters.getMaxHeightPixel() - (this->body->GetWorldCenter().y * gameParameters.getPositionAdjustment()), this->typeFocus, NO_EXPLODE);
}

void Banana::passTime() {
    if (collided) {
        time = std::chrono::steady_clock::now();
        if (time - startTime >= waitTime && !exploded){
            explode();
        }
    }
}

void Banana::explode() {
    std::cout << "Se explota la Banana\n";
    this->exploded = true;
    explodable.searchWormAndCollide(body->GetWorldCenter(), world);
    this->destroyBody();
}

