//
// Created by abraham on 29/10/23.
//

#include "BeamDTO.h"
BeamDTO::BeamDTO() : DTO(BEAM), xCenter(0), yCenter(0), typeBeam(SHORT_BEAM), length(0), height(0), angle(0) {
}

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
    this->height = aHeight;
}

void BeamDTO::setAngle(const size_t &aAngle) {
    this->angle = aAngle;
}

int BeamDTO::getXCenter() const {
    return xCenter;
}

int BeamDTO::getYCenter() const {
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

bool BeamDTO::operator==(const BeamDTO& other) const {
    return  this->opType == other.opType &&
            this->typeBeam == other.typeBeam &&
            this->xCenter == other.xCenter &&
            this->yCenter == other.yCenter &&
            this->length == other.length &&
            this->height == other.height &&
            this->angle == other.angle;
}
