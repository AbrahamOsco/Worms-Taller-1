//
// Created by abraham on 14/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILEDTO_H
#define WORMS_TALLER_1_PROJECTILEDTO_H

#include <cstddef>
#include "DTO.h"

enum TypeProjectil{
    NONE_PROJECTILE,
    BAZOOKA_PROJECTILE,
    AIR_ATTACK_MISSILE,
    DYNAMITE,

};

enum TypeExplode{
    EXPLODE, NO_EXPLODE
};

class ProjectileDTO : public DTO {
private:
    TypeProjectil typeProjectil;
    size_t positionX;
    size_t positionY;
    TypeFocus typeFocus;
    TypeExplode typeExplode;
public:
    ProjectileDTO();

    ProjectileDTO(const TypeProjectil &typeProjectil, const size_t &positionX, const size_t &positionY,
                  const TypeFocus &typeFocus, const TypeExplode& typeExplode);

    TypeProjectil getTypeProjectil() const;

    void setTypeProjectil(const TypeProjectil &typeProjectil);

    size_t getPositionX() const;

    void setPositionX(const size_t &positionX);

    size_t getPositionY() const;

    void setPositionY(const size_t &positionY);

    TypeFocus getTypeFocus() const;

    TypeExplode getTypeExplode() const;

    void setTypeExplode(const TypeExplode &typeExplode);

};


#endif //WORMS_TALLER_1_PROJECTILEDTO_H
