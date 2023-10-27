#include "ClientProtocol.h"

#include "../../../Common/DTO/InitialStateDTO.h"
#define SUCCESS 1
#define ERROR 2

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

// ---------------Comunicacion inicial metodos

void ClientProtocol::sendInitialStateDTO(const InitialStateDTO &initialStateDto) {
    uint8_t typeOperation = initialStateDto.getOperationType();
    std::string playerName = initialStateDto.getPlayerName();

    sendANumberByte(typeOperation);
    sendString(playerName);
}

ResolverInitialDTO ClientProtocol::recvResolverInitialDTO() {
    ResolverInitialDTO resolverInitialDto;
    int typeOperation = recvANumberByte();

    if (typeOperation == RESPONSE_INITIAL_CREATE_GAME ){
        size_t numberScenarios = recvANumberByte();
        std::vector<std::string> scenarioNames;
        for(size_t i = 0; i < numberScenarios ; i++){
            scenarioNames.push_back(recvString());
        }
        resolverInitialDto.setOperationType(RESPONSE_INITIAL_CREATE_GAME);
        resolverInitialDto.setScenarioNames(scenarioNames);
    } else if ( typeOperation == RESPONSE_FINAL_CREATE_GAME ){
        resolverInitialDto.setOperationType( RESPONSE_FINAL_CREATE_GAME);
        resolverInitialDto.setStatusAnswer( recvANumberByte() );
    } else if (typeOperation == RESPONSE_INITIAL_JOIN_GAME){
        resolverInitialDto.setOperationType(RESPONSE_INITIAL_JOIN_GAME);
        size_t numberRooms = recvANumberByte();
        std::vector<RoomDTO> gameRooms;
        for( size_t i = 0; i < numberRooms; i++){
            gameRooms.push_back(recvRoom());
        }
        resolverInitialDto.setGameRooms(gameRooms);
    } else if (typeOperation == RESPONSE_FINAL_JOIN_GAME){
        resolverInitialDto.setOperationType(RESPONSE_FINAL_JOIN_GAME);
        resolverInitialDto.setStatusAnswer(recvANumberByte());
        if(resolverInitialDto.getStatusAnswer() == ERROR ){
            // si es error recibimos los nuevos rooms disponibles.
            size_t numberRooms = recvANumberByte();
            std::vector<RoomDTO> gameRooms;
            for( size_t i = 0; i < numberRooms; i++){
                gameRooms.push_back(recvRoom());
            }
            resolverInitialDto.setGameRooms(gameRooms);
        }
    }
    return resolverInitialDto;
}


RoomDTO ClientProtocol::recvRoom() {
    RoomDTO roomDto;
    int operationType = recvANumberByte();
    if ( operationType == ROOM_GAME){
        roomDto.setGameName(recvString());
        roomDto.setScenarioName(recvString());
        roomDto.setPlayerCurent( recvANumberByte() );
        recvRoom().setPlayerRequired( recvANumberByte());
    }
    return roomDto;
}

void ClientProtocol::sendResponseInitialStateDTO(const ResponseInitialStateDTO &responseInitial) {
    int operationType = responseInitial.getOperationType();
    if ( operationType == FINAL_CREATE_GAME){
        sendANumberByte(FINAL_CREATE_GAME);
        sendString( responseInitial.getGameName() );
        sendString( responseInitial.getScenarioName());
        sendANumberByte(  responseInitial.getPlayerRequired() );
    } else if ( operationType == FINAL_JOIN_GAME){
        sendANumberByte(FINAL_JOIN_GAME);
        sendString(responseInitial.getGameName());
    }

}


ClientProtocol::~ClientProtocol() = default;
