//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_GAMECONTACTLISTENER_H
#define WORMS_TALLER_1_GAMECONTACTLISTENER_H


#include <map>
#include <utility>
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"
#include "../../../GameParameters/GameParameters.h"

class GameContactListener : public b2ContactListener{
 private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *, GameParameters*);
    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;
    std::map<std::pair<Entity, Entity>, HitFunctionPtr> endContactMap;
    GameParameters *gameParameters;
 public:
    explicit GameContactListener(b2World *world, GameParameters *gameParameters);

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
};


#endif  // WORMS_TALLER_1_GAMECONTACTLISTENER_H
