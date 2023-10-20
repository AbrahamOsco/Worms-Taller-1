#ifndef PROTOCOLO_SERVER_BEAMDTO_H
#define PROTOCOLO_SERVER_BEAMDTO_H

#include "common_DTO.h"

class BeamDTO : public DTO {
public:
    enum BeamType {
        LONG = 0,
        SHORT = 1
    };

private:
    DTO::OpType opType;
    int x;
    int y;
    int angle;
    BeamDTO::BeamType type;

public:
    BeamDTO(int x, int y, int angle, BeamDTO::BeamType type);

    int getOpType() override;
    int getBeamType();
    int getX() const;
    int getY() const;
    int getAngle() const;
};


#endif //PROTOCOLO_SERVER_BEAMDTO_H
