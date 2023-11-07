//
// Created by abraham on 03/11/23.
//

#include "Water.h"
#include "box2d/box2d.h"

Water::Water() : GameObject(ENTITY_WATER) {

}

Water::Water(b2World *world, const float &height, const float &width) : GameObject(ENTITY_WATER)  {
    b2BodyDef bd;
    bd.userData.pointer = (uintptr_t) this;
    body = world->CreateBody(&bd);

    b2EdgeShape shape;
    shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(width, 0.0f));
    body->CreateFixture(&shape, 0.0f);
}