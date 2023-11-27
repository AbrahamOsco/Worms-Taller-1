//
// Created by abraham on 17/11/23.
//

#ifndef WORMS_TALLER_1_POSITIONINAREAISFREEQUERY_H
#define WORMS_TALLER_1_POSITIONINAREAISFREEQUERY_H
#include "box2d/box2d.h"

class PositionInAreaisFreeQuery : public b2QueryCallback {
 private:
    bool positionIsFree;

 public:
    PositionInAreaisFreeQuery();

    bool ReportFixture(b2Fixture* fixture);

    bool getPositionIsFree() const;
};


#endif  // WORMS_TALLER_1_POSITIONINAREAISFREEQUERY_H
