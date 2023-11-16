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
    size_t idPlayer;
public:
    StageDTO();

    StageDTO(const std::vector<BeamDTO>& beams);

    void setBeams(const std::vector<BeamDTO>& beams);

    std::vector<BeamDTO> getBeams() const;

    size_t getIdPlayer() const;

    void setIdPlayer(const size_t &idPlayer);

};


#endif //WORMS_TALLER_1_STAGEDTO_H
