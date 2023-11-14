//
// Created by abraham on 13/11/23.
//

#include "SaveWormsInAreaQuery.h"

SaveWormsInAreaQuery::SaveWormsInAreaQuery(const b2Vec2 &munitionPosition){

}

bool SaveWormsInAreaQuery::ReportFixture(b2Fixture* fixture){

}

std::map<GameObject *, float> SaveWormsInAreaQuery::getWormsAndDistSquared() const {
    return this->wormAndDistanceSquar;
}
