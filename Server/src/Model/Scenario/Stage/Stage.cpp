//
// Created by abraham on 28/10/23.
//

#include <iostream>
#include "Stage.h"
#include "../../YamlParser/YamlParser.h"

Stage::Stage(const std::string &name) {
    YamlParser::loadDataStage(name, height, length, beams, idsAndPositionsWorms);
    std::cout << "Positio initial worm CARGADO DEL ARCHIVO SE LEE:  \n";
    std::cout << idsAndPositionsWorms[0].first << ", " << idsAndPositionsWorms[0].second << "\n";

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
void Stage::addToTheWorld(b2World *world) {
    this->edges = Edges(world, height, length);
    this->water = Water(world, height, length);
    for(auto& aBeam : beams){
        aBeam.addToWorld(world);
    }

}



