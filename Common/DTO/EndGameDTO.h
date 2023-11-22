//
// Created by abraham on 18/11/23.
//

#ifndef WORMS_TALLER_1_ENDGAMEDTO_H
#define WORMS_TALLER_1_ENDGAMEDTO_H

#include <cstddef>
#include "DTO.h"

enum TypeResult{
    WON_THE_GAME, LOST_THE_GAME
};

class EndGameDTO : public DTO {
 private:
    size_t idPlayer;
    TypeResult typeResult;

 public:
    EndGameDTO();

    EndGameDTO(const size_t& idPlayer, const TypeResult& typeResult);

    TypeResult getTypeResult() const;

    size_t getIdPlayer() const;

    void setTypeResult(TypeResult typeResult);

    bool operator==(const EndGameDTO& other) const;
};


#endif  // WORMS_TALLER_1_ENDGAMEDTO_H
