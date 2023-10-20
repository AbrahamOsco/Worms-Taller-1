#ifndef PROTOCOLO_COMMON_WORMDTO_H
#define PROTOCOLO_COMMON_WORMDTO_H

#include "common_DTO.h"

class WormDTO : public DTO {
    DTO::OpType opType;
    int x;
    int y;

public:
    WormDTO(int x, int y);

    int getOpType() override;
    int getX() const;
    int getY() const;

};


#endif //PROTOCOLO_COMMON_WORMDTO_H
