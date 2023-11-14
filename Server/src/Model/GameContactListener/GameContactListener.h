//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_GAMECONTACTLISTENER_H
#define WORMS_TALLER_1_GAMECONTACTLISTENER_H


#include <map>
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"

class GameContactListener : public b2ContactListener{
private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);
    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    explicit GameContactListener(b2World *world);

    void BeginContact(b2Contact* contact) override;

};


#endif //WORMS_TALLER_1_GAMECONTACTLISTENER_H
