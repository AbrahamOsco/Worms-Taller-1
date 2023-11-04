//
// Created by abraham on 03/11/23.
//

#include "Edges.h"
#include "box2d/box2d.h"

Edges::Edges(b2World *world, const float &height, const float &width) : GameObject(ENTITY_EDGE) {
    // deberian ser 4 bodys y cada uno con su fixture probarlo y ver q onda porq q aca un body tiene 4 fixture
    // esta ok pero falta ver q tanta complejidad aggrega con las colisiones.
    b2BodyDef bd;
    bd.userData.pointer = (uintptr_t) this;
    body = world->CreateBody(&bd);

    b2EdgeShape shape;
    shape.SetTwoSided(b2Vec2(0.0f, height), b2Vec2(width, height));
    body->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, height));
    body->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(width, 0.0f), b2Vec2(width, height));
    body->CreateFixture(&shape, 0.0f);
}

Edges::Edges() : GameObject(ENTITY_EDGE) {
}
