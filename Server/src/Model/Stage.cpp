//
// Created by abraham on 28/10/23.
//

#include "Stage.h"

Stage::Stage() {
}



Stage::Stage(const std::string &name, const float &height, const float &lenght, const std::vector<Beam> &beams)
                                        : name(name), height(height), length(lenght), beams(beams){
}



StageDTO Stage::getStage() {
    StageDTO stageDto;

    return stageDto;
}

