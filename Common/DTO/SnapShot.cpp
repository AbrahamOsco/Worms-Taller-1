//
// Created by abraham on 06/11/23.
//

#include "SnapShot.h"

SnapShot::SnapShot() : DTO(SNAP_SHOT) {

}

SnapShot::SnapShot(const std::vector<WormDTO> &wormsDTO) : DTO(SNAP_SHOT) {
    this->wormsDTO = wormsDTO;
}

void SnapShot::setWormsDTO(const std::vector<WormDTO> &wormsDTO) {
    this->wormsDTO = wormsDTO;
}

const std::vector<WormDTO> &SnapShot::getWormsDto() const {
    return wormsDTO;
}



