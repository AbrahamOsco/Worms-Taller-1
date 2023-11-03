//
// Created by abraham on 28/10/23.
//

#include "Stage.h"
#include "YamlParser.h"

Stage::Stage(const std::string &name) {
    YamlParser::loadDataStage(name, height, length, beams, idsAndPositionsWorms);
}

StageDTO Stage::getStageDTO() const {
    std::vector<BeamDTO> beamsDTO;
    for(Beam aBeam : beams){
        beamsDTO.push_back(aBeam.getBeamDTO());
    }
    StageDTO stageDto(beamsDTO);
    return stageDto;
}

std::map<size_t, std::pair<float, float>> Stage::getIdsAndPositionsWorms() const {
    return this->idsAndPositionsWorms;
}

// por cada beam creamos su body y lo agregamos al mundo.
void Stage::addBeamsToWorld(b2World *world) {
    // agregamos primero las vigas.
    for(auto& aBeam : beams){

        aBeam.getBeamDTO();
    }
}



