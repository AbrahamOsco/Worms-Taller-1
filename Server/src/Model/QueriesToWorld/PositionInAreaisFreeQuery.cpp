//
// Created by abraham on 17/11/23.
//

#include <iostream>
#include "PositionInAreaisFreeQuery.h"
#include "../GameObject/GameObject.h"

PositionInAreaisFreeQuery::PositionInAreaisFreeQuery() : positionIsFree(true) {
}

bool PositionInAreaisFreeQuery::ReportFixture(b2Fixture *fixture) {
    this->positionIsFree = false;
    return false;
}

bool PositionInAreaisFreeQuery::getPositionIsFree() const {
    return this->positionIsFree;
}
