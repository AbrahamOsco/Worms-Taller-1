//
// Created by abraham on 29/10/23.
//

#include "Beam.h"
#include "box2d/b2_world.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "../../../../GameParameters/GameParameters.h"


Beam::Beam() : GameObject(ENTITY_BEAM), typeBeam(SHORT_BEAM), xCenter(0), yCenter(0), length(0),
                height(0), angle(0) {
}

Beam::Beam(const TypeBeam &aTypeBeam, const float &aXcenter, const float &aYCenter, const float &aLength,
           const float &aHeight, const float &aAngle) : GameObject(ENTITY_BEAM) , typeBeam(aTypeBeam),
           xCenter(aXcenter), yCenter(aYCenter), length(aLength), height(aHeight), angle(aAngle) {
}
BeamDTO Beam::getBeamDTO() {
    BeamDTO beamDto(typeBeam, xCenter * GameParameters::getPositionAdjustmentStatic(),
    GameParameters::getMaxHeightPixelStatic()  - (yCenter * GameParameters::getPositionAdjustmentStatic()),
            length, height, angle);
    return beamDto;
}

void Beam::addToWorld(b2World *world) {
    b2BodyDef defBeam;
    defBeam.type = b2_staticBody;
    defBeam.position.Set(xCenter, yCenter);
    defBeam.userData.pointer = (uintptr_t) this;
    this->body = world->CreateBody(&defBeam);

    float angleRandians = this->angle/180.0f * b2_pi;
    b2PolygonShape shapeBeam;
    shapeBeam.SetAsBox(length/2.0f, height/2.0f, b2Vec2(0.0f, 0.0f), angleRandians);

    b2FixtureDef defFixtureBeam;
    defFixtureBeam.shape = &shapeBeam;
    float beamFriction = GameParameters::getBeamFriction();
    if ( (angle > GameParameters::getBeamMinimumScalableAngle() && angle <
            GameParameters::getBeamMaximumUnscalableAngle() ) ) {
        beamFriction = GameParameters::getBeamFrictionSlipperyStatic();
    }
    defFixtureBeam.friction = beamFriction;
    this->body->CreateFixture(&defFixtureBeam);
}

float Beam::getAngle() const {
    return this->angle;
}


