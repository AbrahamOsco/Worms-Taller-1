//
// Created by abraham on 03/11/23.
//

#include "Edges.h"
#include "box2d/box2d.h"
#include "../../../../GameParameters/GameParameters.h"
#define OFFSET_Y_SECOND_BARRIED -1.0
Edges::Edges(b2World *world, const float &height, const float &width) : GameObject(ENTITY_EDGE) {
    // deberian ser 4 bodys y cada uno con su fixture probarlo y ver q onda porq q aca un body tiene 4 fixture
    // esta ok pero falta ver q tanta complejidad aggrega con las colisiones.
    b2BodyDef bd;
    bd.userData.pointer = (uintptr_t) this;
    body = world->CreateBody(&bd);
    b2EdgeShape shape;
    float heightOffset = height + GameParameters::getOffsetEdgeTop();
    float widthOffset = width + GameParameters::getOffsetWidth();
    shape.SetTwoSided(b2Vec2(0.0f, heightOffset), b2Vec2(widthOffset, heightOffset));
    body->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, heightOffset));
    body->CreateFixture(&shape, 0.0f);
    shape.SetTwoSided(b2Vec2(widthOffset, 0.0f), b2Vec2(widthOffset, heightOffset));
    body->CreateFixture(&shape, 0.0f);

    // creamos ahora 2 capas externas laterales
    shape.SetTwoSided(b2Vec2(-GameParameters::getOffsetLateral(), GameParameters::getOffsetSecondBarrier() ), b2Vec2(GameParameters::getOffsetLateral(), heightOffset));
    body->CreateFixture(&shape, 0.0f);

    shape.SetTwoSided(b2Vec2(widthOffset +GameParameters::getOffsetLateral(), GameParameters::getOffsetSecondBarrier() ), b2Vec2(widthOffset+GameParameters::getOffsetLateral(), heightOffset));
    body->CreateFixture(&shape, 0.0f);

    // creo el suelo debajo del water.  de esta manera ninguna proyectil se qeudara cayendo en el infinito.
    shape.SetTwoSided(b2Vec2(-GameParameters::getOffsetLateral(), GameParameters::getOffsetSecondBarrier()), b2Vec2(widthOffset + GameParameters::getOffsetLateral(), GameParameters::getOffsetSecondBarrier()));
    body->CreateFixture(&shape, 0.0f);
}


Edges::Edges() : GameObject(ENTITY_EDGE) {

}
