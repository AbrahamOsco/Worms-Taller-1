//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_RESPONSECREATEGAMEDTO_H
#define WORMS_TALLER_1_RESPONSECREATEGAMEDTO_H


#include <string>
#include <vector>
#include "DTO.h"

class ResponseCreateGameDTO : public DTO {
private:
    std::vector<std::string> scenariosNames;
    uint8_t statusAnswer;

public:
    ResponseCreateGameDTO();

    void setScenarioNames(const std::vector<std::string>& scenariosNames);


};


#endif //WORMS_TALLER_1_RESPONSECREATEGAMEDTO_H
