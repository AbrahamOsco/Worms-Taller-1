//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_STAGE_H
#define WORMS_TALLER_1_STAGE_H


#include <string>
#include "../../../Common/DTO/StageDTO.h"
#include "Beam.h"

class Stage {
private:
    std::string name;
    float height;
    float length;
    std::vector<Beam> beams;
public:

    Stage();

    Stage(const std::string& name, const float& height, const float& lenght, const std::vector<Beam>& beams);

    StageDTO getStage();

};


#endif //WORMS_TALLER_1_STAGE_H
