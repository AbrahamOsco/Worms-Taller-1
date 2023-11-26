//
// Created by abraham on 28/10/23.
//

#include <iostream>
#include "Stage.h"
#include "../../YamlParser/YamlParser.h"
#include "../../../../GameParameters/GameParameters.h"

Stage::Stage(const std::string &name) {
    YamlParser::loadDataStage(name, height, length, beams, idsAndPositionsWorms, background);
}

StageDTO Stage::getStageDTO() const {
    std::vector<BeamDTO> beamsDTO;
    for (Beam aBeam : beams) {
        beamsDTO.push_back(aBeam.getBeamDTO());
    }
    float posYCenter = GameParameters::getOffsetWater() +water->getBody()->GetWorldCenter().y;
    size_t positionY = (GameParameters::getMaxHeightPixelStatic()  - (posYCenter *
            GameParameters::getPositionAdjustmentStatic()));
    StageDTO stageDto(beamsDTO, positionY, background);
    return stageDto;
}

std::map<size_t, std::pair<float, float>> Stage::getIdsAndPositionsWorms() const {
    return this->idsAndPositionsWorms;
}

// por cada beam creamos su body y lo agregamos al mundo.
void Stage::addToTheWorld(b2World *world) {
    this->edges = std::make_unique<Edges>(world, height, length);
    this->water = std::make_unique<Water>(world, height, length);
    for (auto& aBeam : beams) {
        aBeam.addToWorld(world);
    }
}



