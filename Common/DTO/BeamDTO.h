//
// Created by abraham on 29/10/23.
//

#ifndef WORMS_TALLER_1_BEAMDTO_H
#define WORMS_TALLER_1_BEAMDTO_H


#include <cstddef>
#include "DTO.h"

enum TypeBeam {
    SHORT_BEAM = 3 , LONG_BEAM = 6, WATER_BEAM = 1500
};

class BeamDTO : public DTO {
 private:
    TypeBeam typeBeam;
    int xCenter;
    int yCenter;
    size_t length;
    size_t height;
    size_t angle;

 public:
    BeamDTO();

    BeamDTO(const TypeBeam& aTypeBeam, const size_t& aXcenter, const size_t& aYCenter,
           const size_t& aLength, const size_t& aHeight, const size_t& aAngle);

    void setTypeBeam(const TypeBeam& aTypeBeam);

    void setxCenter(const size_t& aXcenter);

    void setYCenter(const size_t& aYCenter);

    void setLength(const size_t& aLength);

    void setHeight(const size_t& aHeight);

    void setAngle(const size_t& aAngle);

    TypeBeam getTypeBeam() const;

    int getXCenter() const;

    int getYCenter() const;

    size_t getLenghth() const;

    size_t getHeight() const;

    size_t getAngle() const;

    bool operator==(const BeamDTO& other) const;
};

#endif  // WORMS_TALLER_1_BEAMDTO_H
