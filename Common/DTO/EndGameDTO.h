//
// Created by abraham on 18/11/23.
//

#ifndef WORMS_TALLER_1_ENDGAMEDTO_H
#define WORMS_TALLER_1_ENDGAMEDTO_H

#include "DTO.h"

enum TypeResult{
    WON_THE_GAME, LOST_THE_GAME
};

class EndGameDTO : public DTO {
private:
    TypeResult typeResult;

public:
    EndGameDTO(const TypeResult& typeResult);

    TypeResult getTypeResult() const;

    void setTypeResult(TypeResult typeResult);

    EndGameDTO();
};


#endif //WORMS_TALLER_1_ENDGAMEDTO_H
