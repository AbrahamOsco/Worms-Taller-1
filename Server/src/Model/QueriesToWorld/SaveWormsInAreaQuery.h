//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_SAVEWORMSINAREAQUERY_H
#define WORMS_TALLER_1_SAVEWORMSINAREAQUERY_H

#include <map>
#include "box2d/box2d.h"
#include "../GameObject/GameObject.h"

class SaveWormsInAreaQuery : public b2QueryCallback {
 private:
    std::map<GameObject*, float> wormAndDistanceSquar;
    b2Vec2 munitionPosition;

 public:
    explicit SaveWormsInAreaQuery(const b2Vec2 &munitionPosition);

    bool ReportFixture(b2Fixture* fixture) override;

    std::map<GameObject*, float>  getWormsAndDistSquared() const;
};


#endif  // WORMS_TALLER_1_SAVEWORMSINAREAQUERY_H
