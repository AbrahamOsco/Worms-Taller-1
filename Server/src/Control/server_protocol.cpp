#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket& skt) :
        Protocol(skt){}

void ServerProtocol::sendMap(MapDTO& aMap) {

    OpType op = aMap.getOpType();
    Protocol::sendANumberByte(op);

    uint16_t numBeams = aMap.getNumBeams();
    Protocol::sendNum2Bytes(numBeams);

    std::vector<BeamDTO>& beams = aMap.getBeams();
    for (auto & beam : beams) {
        sendBeam(beam);
    }
}

void ServerProtocol::sendBeam(BeamDTO& aBeam) {
    OpType op = aBeam.getOpType();
    Protocol::sendANumberByte(op);

    BeamType beamType = aBeam.getBeamType();
    Protocol::sendANumberByte(beamType);

    int xCoord = aBeam.getX();
    Protocol::sendNum2Bytes(xCoord);

    int yCoord = aBeam.getY();
    Protocol::sendNum2Bytes(yCoord);

    int angle = aBeam.getAngle();
    Protocol::sendNum2Bytes(angle);
}

void ServerProtocol::sendWorm(WormDTO& aWorm) {
    OpType op = aWorm.getOpType();
    Protocol::sendANumberByte(op);

    int xCoord = aWorm.getX();
    Protocol::sendNum2Bytes(xCoord);

    int yCoord = aWorm.getY();
    Protocol::sendNum2Bytes(yCoord);
}

ServerProtocol::~ServerProtocol() = default;
