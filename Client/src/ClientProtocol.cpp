#include "ClientProtocol.h"

ClientProtocol::ClientProtocol(Socket& skt) :
        Protocol(skt) {}

MapDTO ClientProtocol::recvMap() {
    auto opType = static_cast<OperationType>(recvANumberByte());
    if (opType != OperationType::MAP) {
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
    auto opType = static_cast<OperationType>(recvANumberByte());
    if (opType != OperationType::BEAM) {
        // no se si conviene exception o return beam vacio.
    }

    int beamTypeInt = recvANumberByte();
    auto beamType = static_cast<BeamType>(beamTypeInt);

    int xCoord = recvNum2Bytes();

    int yCoord = recvNum2Bytes();

    int angle = recvNum2Bytes();

    BeamDTO beam(xCoord, yCoord, angle, beamType);
    return beam;
}

WormDTO ClientProtocol::recvWorm() {
    auto opType = static_cast<OperationType>(recvANumberByte());
    if (opType != OperationType::WORM) {
        // no se si conviene exception o return worm vacio.
    }

    int xCoord = recvNum2Bytes();

    int yCoord = recvNum2Bytes();

    WormDTO worm(xCoord, yCoord);
    return worm;
}

ClientProtocol::~ClientProtocol() = default;
