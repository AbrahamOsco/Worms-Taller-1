//
// Created by abraham on 29/10/23.
//

#ifndef WORMS_TALLER_1_STAGEDTO_H
#define WORMS_TALLER_1_STAGEDTO_H


#include <vector>
#include <string>
#include "DTO.h"
#include "BeamDTO.h"

class StageDTO : public DTO {
 private:
    std::vector<BeamDTO> beams;
    size_t idPlayer;
    size_t positionYWater;
    std::string background;

 public:
    StageDTO();

    explicit StageDTO(const std::vector<BeamDTO>& beams, const size_t& positionYWater, const std::string& background);

    void setBeams(const std::vector<BeamDTO>& beams);

    std::vector<BeamDTO> getBeams() const;

    size_t getIdPlayer() const;

    void setIdPlayer(const size_t &idPlayer);

    size_t getPositionYWater() const;

    void setPositionYWater(const size_t &positionYWater);

    std::string getBackground() const;

    void setBackground(const std::string &background);

    bool operator==(const StageDTO& other) const;
};


#endif  // WORMS_TALLER_1_STAGEDTO_H
