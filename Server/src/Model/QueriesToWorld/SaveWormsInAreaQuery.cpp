//
// Created by abraham on 13/11/23.
//

#include <iostream>
#include "SaveWormsInAreaQuery.h"

SaveWormsInAreaQuery::SaveWormsInAreaQuery(const b2Vec2 &munitionPosition) {
    this->munitionPosition = munitionPosition;
}

bool SaveWormsInAreaQuery::ReportFixture(b2Fixture* fixture) {
    GameObject* obj = (GameObject*) (fixture->GetBody()->GetUserData().pointer);
    if (obj && obj->getEntityType() == ENTITY_WORM) {
        float distanceSquared = b2DistanceSquared(munitionPosition, fixture->GetBody()->GetWorldCenter());
        wormAndDistanceSquar[obj] = distanceSquared;
    }
    return true;
}

std::map<GameObject *, float> SaveWormsInAreaQuery::getWormsAndDistSquared() const {
    return this->wormAndDistanceSquar;
}
