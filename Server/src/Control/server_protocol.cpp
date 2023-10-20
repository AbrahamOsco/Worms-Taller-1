#include "server_protocol.h"

#include <iostream>

ServerProtocol::ServerProtocol(Socket&& skt) :
        Protocol(std::move(skt)){}

void ServerProtocol::sendMap(MapDTO& aMap) {

    int op = aMap.getOpType();
    Protocol::sendANumberByte(op);

    uint16_t numBeams = aMap.getNumBeams();
    Protocol::sendNum2Bytes(numBeams);

    std::vector<BeamDTO>& beams = aMap.getBeams();
    for (auto & beam : beams) {
        sendBeam(beam);
    }
}

void ServerProtocol::sendBeam(BeamDTO& aBeam) {
    uint8_t op = aBeam.getOpType();
    Protocol::sendANumberByte(op);

    uint8_t beamType = aBeam.getBeamType();
    Protocol::sendANumberByte(beamType);

    int xCoord = aBeam.getX();
    Protocol::sendNum2Bytes(xCoord);

    int yCoord = aBeam.getY();
    Protocol::sendNum2Bytes(yCoord);

    int angle = aBeam.getAngle();
    Protocol::sendNum2Bytes(angle);
}

void ServerProtocol::sendWorm(WormDTO& aWorm) {
    uint8_t op = aWorm.getOpType();
    Protocol::sendANumberByte(op);

    int xCoord = aWorm.getX();
    Protocol::sendNum2Bytes(xCoord);

    int yCoord = aWorm.getY();
    Protocol::sendNum2Bytes(yCoord);
}
