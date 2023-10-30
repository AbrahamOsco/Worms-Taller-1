//
// Created by abraham on 29/10/23.
//

#ifndef WORMS_TALLER_1_STAGEDTO_H
#define WORMS_TALLER_1_STAGEDTO_H


#include <vector>
#include "DTO.h"
#include "BeamDTO.h"

class StageDTO : public DTO {
private:
    std::vector<BeamDTO> beams;
public:
    StageDTO();

    StageDTO(const std::vector<BeamDTO>& beams);

    void setBeams(const std::vector<BeamDTO>& beams);

    std::vector<BeamDTO> getBeams() const;

};


#endif //WORMS_TALLER_1_STAGEDTO_H
