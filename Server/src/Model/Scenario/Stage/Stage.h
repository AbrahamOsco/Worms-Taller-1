//
// Created by abraham on 28/10/23.
//

#ifndef WORMS_TALLER_1_STAGE_H
#define WORMS_TALLER_1_STAGE_H


#include <string>
#include <map>
#include "../../../../../Common/DTO/StageDTO.h"
#include "../Beam/Beam.h"
#include "box2d/b2_world.h"
#include "../Edges/Edges.h"
#include "../Water/Water.h"

class Stage {
private:
    std::string name;
    float height;
    float length;
    std::vector<Beam> beams;
    std::map<size_t, std::pair<float, float>> idsAndPositionsWorms;
    Edges edges;
    Water water;
public:

    Stage(const std::string& name);

    std::map<size_t, std::pair<float, float>> getIdsAndPositionsWorms() const;

    StageDTO getStageDTO() const;


    void addToTheWorld(b2World *world);
};


#endif //WORMS_TALLER_1_STAGE_H
