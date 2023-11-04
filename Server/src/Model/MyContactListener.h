//
// Created by abraham on 03/11/23.
//

#ifndef WORMS_TALLER_1_MYCONTACTLISTENER_H
#define WORMS_TALLER_1_MYCONTACTLISTENER_H


#include <map>
#include "GameObject.h"
#include "box2d/box2d.h"

class MyContactListener : public b2ContactListener {
private:
    typedef void (*HitFunctionPtr)(GameObject *, GameObject *);

    std::map<std::pair<Entity, Entity>, HitFunctionPtr> collisionsMap;

public:
    MyContactListener(b2World *world);

    void BeginContact(b2Contact* contact);

    ~MyContactListener() = default;
};


#endif //WORMS_TALLER_1_MYCONTACTLISTENER_H
