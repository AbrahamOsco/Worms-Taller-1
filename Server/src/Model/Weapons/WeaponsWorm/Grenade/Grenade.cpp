//
// Created by abraham on 22/11/23.
//

#include "Grenade.h"

Grenade::Grenade(GameParameters gameParameters) : GameObject(ENTITY_GRENADE), gameParameters(gameParameters), weaponSight(3.0f, 2.0f, gameParameters) {

}
