//
// Created by abraham on 29/10/23.
//

#ifndef WORMS_TALLER_1_BEAMDTO_H
#define WORMS_TALLER_1_BEAMDTO_H


#include <cstddef>
#include "DTO.h"
#include "../../Server/src/Model/Beam.h"

enum TypeBeam {
    SHORT_BEAM = 1 , LONG_BEAM = 2
};

class BeamDTO : public DTO {
private:
    TypeBeam typeBeam;
    size_t xCenter;
    size_t yCenter;
    size_t length;
    size_t height;
    size_t angle;
public:

    BeamDTO(const TypeBeam& aTypeBeam, const size_t& aXcenter, const size_t& aYCenter, const size_t& aLength, const size_t& aHeight, const size_t& aAngle);

    void setTypeBeam(const TypeBeam& aTypeBeam);

    void setxCenter(const size_t& aXcenter);

    void setYCenter(const size_t& aYCenter);

    void setLength(const size_t& aLength);

    void setHeight(const size_t& aHeight);

    void setAngle(const size_t& aAngle);

    size_t getXCenter() const;

    size_t getYCenter() const;

    size_t getLenghth() const;

    size_t getHeight() const;

    size_t getAngle() const;

    TypeBeam getTypeBeam() const;

};


#endif //WORMS_TALLER_1_BEAMDTO_H
