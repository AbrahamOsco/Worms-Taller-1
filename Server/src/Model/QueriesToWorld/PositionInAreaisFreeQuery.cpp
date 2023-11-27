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
    GameObject* obj = (GameObject*) (fixture->GetBody()->GetUserData().pointer);
    if (obj) {
        std::cout << "Soy el objeto del tipo" << obj->getEntityType() << " y mi posicionCenter x: " <<
        obj->getBody()->GetWorldCenter().x << "  y : " <<  obj->getBody()->GetWorldCenter().y;
    }
    return false;
}

bool PositionInAreaisFreeQuery::getPositionIsFree() const {
    return this->positionIsFree;
}
