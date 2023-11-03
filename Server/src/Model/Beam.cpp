//
// Created by abraham on 29/10/23.
//

#include "Beam.h"

Beam::Beam(){
}

Beam::Beam(const TypeBeam &aTypeBeam, const float &aXcenter, const float &aYCenter, const float &aLength, const float &aHeight, const float &aAngle)
    : typeBeam(aTypeBeam), xCenter(aXcenter), yCenter(aYCenter), length(aLength), height(aHeight), angle(aAngle) {

}

BeamDTO Beam::getBeamDTO() {
    float coordYClient = yCenter* (-1);
    BeamDTO beamDto(typeBeam, xCenter, coordYClient, length, height, angle);
    return beamDto;
}


