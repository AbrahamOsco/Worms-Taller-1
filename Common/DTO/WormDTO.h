#ifndef PROTOCOLO_COMMON_WORMDTO_H
#define PROTOCOLO_COMMON_WORMDTO_H

#include "DTO.h"

class WormDTO : public DTO {
    int x;
    int y;

public:
    WormDTO(int x, int y);

    int getX() const;
    int getY() const;
    ~WormDTO();

};


#endif //PROTOCOLO_COMMON_WORMDTO_H
