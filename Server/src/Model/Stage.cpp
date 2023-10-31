//
// Created by abraham on 28/10/23.
//

#include "Stage.h"
#include "YamlParser.h"
Stage::Stage() {
}

Stage::Stage(const std::string &name) {
    YamlParser::loadDataStage(name, height, length, beams);
}

StageDTO Stage::getStageDTO() const {
    std::vector<BeamDTO> beamsDTO;
    for(Beam aBeam : beams){
        beamsDTO.push_back(aBeam.getBeamDTO());
    }
    StageDTO stageDto(beamsDTO);
    return stageDto;
}


