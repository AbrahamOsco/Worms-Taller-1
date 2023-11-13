//
// Created by abraham on 13/11/23.
//

#ifndef WORMS_TALLER_1_WEAPONSIGHTDTO_H
#define WORMS_TALLER_1_WEAPONSIGHTDTO_H


#include <cstddef>
#include "DTO.h"

enum TypeSight{
    SHOW_SIGHT,
    NO_SHOW_SIGHT
};

class WeaponSightDTO : public DTO {
private:
    TypeSight typeSight;
    size_t positionXSight;
    size_t positionYSight;
public:
    WeaponSightDTO();

    WeaponSightDTO(const TypeSight &typeSight, const size_t& positionXSight, const size_t positionYSight);

    TypeSight getTypeSight() const;

    size_t getPositionXSight() const;

    size_t getPositionYSight() const;

    void setTypeSight(const TypeSight &typeSight);

    void setPositionXSight(const size_t &positionXSight);

    void setPositionYSight(const size_t &positionYSight);

};


#endif //WORMS_TALLER_1_WEAPONSIGHTDTO_H
