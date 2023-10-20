#ifndef PROTOCOLO_SERVER_BEAMDTO_H
#define PROTOCOLO_SERVER_BEAMDTO_H

#include "common_DTO.h"

enum BeamType {
    LONG = 0,
    SHORT = 1
};

class BeamDTO : public DTO {
    int x;
    int y;
    int angle;
    BeamType type;

public:
    BeamDTO(int x, int y, int angle, BeamType type);

    BeamType getBeamType();
    int getX() const;
    int getY() const;
    int getAngle() const;
    ~BeamDTO() override;
};


#endif //PROTOCOLO_SERVER_BEAMDTO_H
