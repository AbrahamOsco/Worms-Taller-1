//
// Created by abraham on 14/11/23.
//

#include "ProjectilesDTO.h"

ProjectilesDTO::ProjectilesDTO() : DTO(PROJECTILES_DTO), typeShowProjectiles(NO_SHOW_PROJECTILES) {}

ProjectilesDTO::ProjectilesDTO(const TypeShowProjectiles &typeShowProjectiles,
                const std::vector<ProjectileDTO> &projectilesDTO) :
                DTO(PROJECTILES_DTO), typeShowProjectiles(typeShowProjectiles), projectilesDTO(projectilesDTO) {
}


std::vector<ProjectileDTO> ProjectilesDTO::getProjectilesDto() const {
    return projectilesDTO;
}

void ProjectilesDTO::setProjectilesDto(const std::vector<ProjectileDTO> &projectilesDto) {
    projectilesDTO = projectilesDto;
}

TypeShowProjectiles ProjectilesDTO::getTypeShowProjectiles() const {
    return typeShowProjectiles;
}

void ProjectilesDTO::setTypeShowProjectiles(const TypeShowProjectiles &typeShowProjectiles) {
    this->typeShowProjectiles = typeShowProjectiles;
}

bool ProjectilesDTO::operator==(const ProjectilesDTO& other) const {
    return  this->opType == other.opType &&
            this->typeShowProjectiles == other.typeShowProjectiles &&
            this->projectilesDTO == other.projectilesDTO;
}
