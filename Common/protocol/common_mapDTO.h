#ifndef WORMS_TALLER_1_SERVER_MAPDTO_H
#define WORMS_TALLER_1_SERVER_MAPDTO_H

#include "common_DTO.h"
#include "common_beamDTO.h"
#include <vector>

class MapDTO : public DTO {
    //size x, size y?
    DTO::OpType opType;
    std::vector<BeamDTO> beams;
public:
    explicit MapDTO(const std::vector<BeamDTO>& beams);

    int getOpType() override;
    unsigned int getNumBeams();
    std::vector<BeamDTO>& getBeams();
};


#endif //WORMS_TALLER_1_SERVER_MAPDTO_H
