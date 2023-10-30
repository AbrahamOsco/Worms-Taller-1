//
// Created by abraham on 29/10/23.
//

#include "BeamDTO.h"

BeamDTO::BeamDTO(const TypeBeam &aTypeBeam, const size_t &aXcenter, const size_t &aYCenter, const size_t &aLength,
                 const size_t &aHeight, const size_t &aAngle) : DTO(BEAM), typeBeam(aTypeBeam), xCenter(aXcenter),
                 yCenter(aYCenter), length(aLength), height(aHeight), angle(aAngle)  {
}

void BeamDTO::setTypeBeam(const TypeBeam &aTypeBeam) {
    this->typeBeam = aTypeBeam;
}

void BeamDTO::setxCenter(const size_t &aXcenter) {
    this->xCenter = aXcenter;
}

void BeamDTO::setYCenter(const size_t &aYCenter) {
    this->yCenter = aYCenter;
}

void BeamDTO::setLength(const size_t &aLength) {
    this->length = aLength;
}

void BeamDTO::setHeight(const size_t &aHeight) {
    this->height =aHeight;
}

void BeamDTO::setAngle(const size_t &aAngle) {
    this->angle = aAngle;
}

size_t BeamDTO::getXCenter() const {
    return xCenter;
}

size_t BeamDTO::getYCenter() const {
    return yCenter;
}

size_t BeamDTO::getLenghth() const {
    return length;
}

size_t BeamDTO::getHeight() const {
    return height;
}

size_t BeamDTO::getAngle() const {
    return angle;
}

TypeBeam BeamDTO::getTypeBeam() const {
    return typeBeam;
}







