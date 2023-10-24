#ifndef WORMS_TALLER_1_SERVER_MAPDTO_H
#define WORMS_TALLER_1_SERVER_MAPDTO_H

#include "DTO.h"
#include "BeamDTO.h"
#include <vector>

class MapDTO : public DTO {
    //size x, size y?
    std::vector<BeamDTO> beams;

public:
    explicit MapDTO(const std::vector<BeamDTO>& beams);

    unsigned int getNumBeams();
    std::vector<BeamDTO>& getBeams();
    ~MapDTO() override;
};


#endif //WORMS_TALLER_1_SERVER_MAPDTO_H
