//
// Created by abraham on 19/11/23.
//

#ifndef WORMS_TALLER_1_PROVISIONDTO_H
#define WORMS_TALLER_1_PROVISIONDTO_H

#include <cstddef>
#include "DTO.h"

enum TypeEffect{
    MUNITIONS, MEDICAL_KIT, EXPLOSION
};

/* //enum  probar primero sin el enum de visibilidad
enum TypeVisionProvision{
    SHOW_PROVISION, NO_SHOW_PROVISION
};
*/

class ProvisionDTO : public DTO {
private:
    size_t positionX;
    size_t positionY;
    TypeEffect typeEffect;

public:
    ProvisionDTO(const size_t& positionX, const size_t& positionY, const TypeEffect& typeEffect);
    size_t getPositionX() const;

    size_t getPositionY() const;

    TypeEffect getTypeEffect() const;

};


#endif //WORMS_TALLER_1_PROVISIONDTO_H
