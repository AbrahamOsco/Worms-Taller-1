#include "ClientProtocol.h"

#include "../../../Common/DTO/InitialStateDTO.h"
#define SUCCESS 1
#define ERROR 2

ClientProtocol::ClientProtocol(Socket& skt) :
        Protocol(skt) {}



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
    } else if (typeOperation == START_GAME){
        resolverInitialDto.setOperationType(START_GAME);
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
        roomDto.setPlayerRequired( recvANumberByte());
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

StageDTO ClientProtocol::recvStageDTO() {
    StageDTO stageDto;
    size_t typeOperation = recvANumberByte();
    if (typeOperation == STAGE){
        size_t numberBeams = recvANumberByte();
        std::vector<BeamDTO> beams;
        for (size_t i = 0 ; i < numberBeams; i++){
            beams.push_back(recvBeamDTO());
        }
        stageDto.setBeams(beams);
    }
    return stageDto;
}

BeamDTO ClientProtocol::recvBeamDTO() {
    BeamDTO beamDto;
    int operationType = recvANumberByte();
    if ( operationType == BEAM){
        size_t typeBeam = recvANumberByte();
        TypeBeam aTypeBeam;
        if(typeBeam == SHORT_BEAM){
            aTypeBeam = SHORT_BEAM;
        } else if (typeBeam == LONG_BEAM){
            aTypeBeam = LONG_BEAM;
        }
        size_t xCenter = recvANumberByte();
        size_t yCenter = recvANumberByte();
        size_t angle = recvANumberByte();
        size_t length = recvANumberByte();
        size_t height = recvANumberByte();
        BeamDTO beamRecv(aTypeBeam, xCenter, yCenter, length, height, angle);
        return beamRecv;
    }
    return beamDto;
}


ClientProtocol::~ClientProtocol() = default;
