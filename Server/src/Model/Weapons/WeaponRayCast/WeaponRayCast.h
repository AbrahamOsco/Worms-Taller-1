//
// Created by abraham on 10/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONRAYCAST_H
#define WORMS_TALLER_1_WEAPONRAYCAST_H


#include "box2d/box2d.h"

class WeaponRayCast : public b2RayCastCallback{
 private:
    b2Body* body;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
 public:
    WeaponRayCast();

    float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override;

    b2Body* getBody() const;

    float getFraction() const;

    void resetRayCast();

    ~WeaponRayCast() = default;
};


#endif  // WORMS_TALLER_1_WEAPONRAYCAST_H
