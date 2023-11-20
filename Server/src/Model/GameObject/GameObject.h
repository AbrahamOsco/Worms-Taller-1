//
// Created by abraham on 30/10/23.
//

#ifndef WORMS_TALLER_1_GAMEOBJECT_H
#define WORMS_TALLER_1_GAMEOBJECT_H

#include "box2d/b2_body.h"
enum Entity{
    ENTITY_BEAM = 0,
    ENTITY_WATER = 1,
    ENTITY_EDGE = 2,
    ENTITY_WORM = 3,
    ENTITY_BAZOOKA_PROJECTILE = 4,
    ENTITY_PROVISION = 15
};


class GameObject {
protected:
    Entity typeEntity;
    b2Body* body;
    bool isDestroyed;

public:
    explicit GameObject(const Entity &aEntity);

    b2Body* getBody();

    Entity getEntityType() const;

    void destroyBody();

    bool isDestroyedBody();

    virtual ~GameObject() = default;

};


#endif //WORMS_TALLER_1_GAMEOBJECT_H
