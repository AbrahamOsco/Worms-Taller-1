#ifndef PROTOCOLO_COMMON_WORMDTO_H
#define PROTOCOLO_COMMON_WORMDTO_H

#include <cstddef>
#include "DTO.h"

class WormDTO : public DTO {

private:
    size_t idWorm;
    size_t positionX;
    size_t positionY;
    // faltaria mandar HP y mas cosas por ahora esos 3.

public:
    WormDTO(const size_t& idWorm, const size_t& positionX, const size_t& positionY);

    size_t getIdWorm() const;

    size_t getPositionX() const;

    size_t getPositionY() const;


    ~WormDTO();

};


#endif //PROTOCOLO_COMMON_WORMDTO_H
