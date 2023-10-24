#include "ServerProtocol.h"

ServerProtocol::ServerProtocol(Socket& skt) :
        Protocol(skt){}

void ServerProtocol::sendMap(const MapDTO &aMap) {

    OpType op = aMap.getOperationType();
    sendANumberByte(op);

    uint16_t numBeams = aMap.getNumBeams();
    sendNum2Bytes(numBeams);

    std::vector<BeamDTO> beams = aMap.getBeams();
    for (auto beam : beams) {
        sendBeam(beam);
    }
}

void ServerProtocol::sendBeam(const BeamDTO &aBeam) {
    OpType op = aBeam.getOperationType();
    sendANumberByte(op);

    BeamType beamType = aBeam.getBeamType();
    sendANumberByte(beamType);

    int xCoord = aBeam.getX();
    sendNum2Bytes(xCoord);

    int yCoord = aBeam.getY();
    sendNum2Bytes(yCoord);

    int angle = aBeam.getAngle();
    sendNum2Bytes(angle);
}

void ServerProtocol::sendWorm(const WormDTO &aWorm) {
    OpType op = aWorm.getOperationType();
    sendANumberByte(op);

    int xCoord = aWorm.getX();
    sendNum2Bytes(xCoord);

    int yCoord = aWorm.getY();
    sendNum2Bytes(yCoord);
}

LobbyAnswerDTO ServerProtocol::recvLobbyAnswer() {
    LobbyAnswerDTO aLobbyAnswer;
    int operationType = static_cast<int>(recvANumberByte());
    if(operationType == CLOSED_CONNECTION){
        return aLobbyAnswer; // cliente cerro la conexion;
    }
    std::string gameName = recvString();
    aLobbyAnswer.setGameName(gameName);
    if (operationType == OpType::CREATE_GAME){
        aLobbyAnswer.setOperationType(OpType::CREATE_GAME);
        std::string nameScenario = recvString();
        aLobbyAnswer.setSelectScenario(nameScenario);
    } else if ( operationType == OpType::JOIN_GAME){
        aLobbyAnswer.setOperationType(OpType::JOIN_GAME);
    }
    return aLobbyAnswer;
}

ServerProtocol::~ServerProtocol() = default;
