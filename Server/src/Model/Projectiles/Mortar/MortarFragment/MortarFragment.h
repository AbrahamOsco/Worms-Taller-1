//
// Created by abraham on 23/11/23.
//

#ifndef WORMS_TALLER_1_MORTARFRAGMENT_H
#define WORMS_TALLER_1_MORTARFRAGMENT_H

#include <vector>
#include "../ProjectileMortar.h"

class MortarFragment : public ProjectileMortar {
 public:
    MortarFragment(const GameParameters &gameParameters, const TypeFocus& typeFocus);

    void getProjectileDTO(std::vector<ProjectileDTO>& vecProjectileDTO) override;
};


#endif  // WORMS_TALLER_1_MORTARFRAGMENT_H
