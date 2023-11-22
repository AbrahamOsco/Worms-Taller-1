//
// Created by abraham on 14/11/23.
//

#ifndef WORMS_TALLER_1_PROJECTILESDTO_H
#define WORMS_TALLER_1_PROJECTILESDTO_H


#include <vector>
#include "ProjectileDTO.h"

enum TypeShowProjectiles{
    SHOW_PROJECTILES, NO_SHOW_PROJECTILES
};

class ProjectilesDTO : public DTO {
 private:
    TypeShowProjectiles typeShowProjectiles;
    std::vector<ProjectileDTO> projectilesDTO;

 public:
    ProjectilesDTO();

    explicit ProjectilesDTO(const TypeShowProjectiles& typeShowProjectiles,
                            const std::vector<ProjectileDTO>& projectilesDTO);

    std::vector<ProjectileDTO> getProjectilesDto() const;

    void setProjectilesDto(const std::vector<ProjectileDTO> &projectilesDto);

    TypeShowProjectiles getTypeShowProjectiles() const;

    void setTypeShowProjectiles(const TypeShowProjectiles &typeShowProjectiles);

    bool operator==(const ProjectilesDTO& other) const;
};


#endif  // WORMS_TALLER_1_PROJECTILESDTO_H
