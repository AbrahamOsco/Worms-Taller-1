//
// Created by abraham on 29/10/23.
//

#ifndef WORMS_TALLER_1_BEAM_H
#define WORMS_TALLER_1_BEAM_H


#include <cstddef>
#include "../../../../../Common/DTO/BeamDTO.h"
#include "../../GameObject/GameObject.h"

class Beam : public GameObject {
 private:
    TypeBeam typeBeam;
    float xCenter;
    float yCenter;
    float length;
    float height;
    float angle;
 public:
    Beam();

    Beam(const TypeBeam &aTypeBeam, const float &aXcenter, const float &aYCenter, const float &aLength,
         const float &aHeight, const float &aAngle);

    BeamDTO getBeamDTO();

    float getAngle() const;

    void addToWorld(b2World *world);

};


#endif  // WORMS_TALLER_1_BEAM_H
