#include "client_protocol.h"

ClientProtocol::ClientProtocol(Socket&& skt) :
        Protocol(std::move(skt)) {}

MapDTO ClientProtocol::recvMap() {
    uint8_t opType = recvANumberByte();
    if (opType != DTO::OpType::MAP) {
        // no se si conviene exception o return mapa vacio.
    }

    uint16_t numBeams = recvNum2Bytes();

    std::vector<BeamDTO> beams;
    for (int i = 0; i < numBeams; i++) {
        BeamDTO beam = recvBeam();
        beams.push_back(beam);
    }

    MapDTO map(beams);
    return map;
}

BeamDTO ClientProtocol::recvBeam() {
    uint8_t opType = recvANumberByte();
    if (opType != DTO::OpType::BEAM) {
        // no se si conviene exception o return beam vacio.
    }

    int beamTypeInt = recvANumberByte();
    auto beamType = static_cast<BeamDTO::BeamType>(beamTypeInt);

    int xCoord = recvNum2Bytes();

    int yCoord = recvNum2Bytes();

    int angle = recvNum2Bytes();

    BeamDTO beam(xCoord, yCoord, angle, beamType);
    return beam;
}

WormDTO ClientProtocol::recvWorm() {
    uint8_t opType = recvANumberByte();
    if (opType != DTO::OpType::WORM) {
        // no se si conviene exception o return worm vacio.
    }

    int xCoord = recvNum2Bytes();

    int yCoord = recvNum2Bytes();

    WormDTO worm(xCoord, yCoord);
    return worm;
}
