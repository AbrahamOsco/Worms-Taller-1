#ifndef WORMS_TALLER_1_SERVER_MAPDTO_H
#define WORMS_TALLER_1_SERVER_MAPDTO_H

#include "DTO.h"
#include "BeamDTO.h"
#include <vector>
#include "../../Common/DTO/DTO.h"

class MapDTO : public DTO {
    //size x, size y?
    std::vector<BeamDTO> beams;

public:
    explicit MapDTO(const std::vector<BeamDTO>& beams);

    unsigned int getNumBeams() const;

    std::vector<BeamDTO> getBeams() const;

    ~MapDTO() override;
};


#endif //WORMS_TALLER_1_SERVER_MAPDTO_H
