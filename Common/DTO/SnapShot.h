//
// Created by abraham on 06/11/23.
//

#ifndef WORMS_TALLER_1_SNAPSHOT_H
#define WORMS_TALLER_1_SNAPSHOT_H


#include <vector>
#include "WormDTO.h"

class SnapShot : public DTO {
private:
    std::vector<WormDTO> wormsDTO;
public:
    SnapShot();

    explicit SnapShot(const std::vector<WormDTO>& wormsDTO);

    void setWormsDTO(const std::vector<WormDTO>& wormsDTO);

    const std::vector<WormDTO> &getWormsDto() const;

};


#endif //WORMS_TALLER_1_SNAPSHOT_H
