#include <iostream>
#include "ClientProtocol.h"

#include "../../../Common/DTO/InitialStateDTO.h"
#define SUCCESS 1
#define ERROR 2

ClientProtocol::ClientProtocol(Socket& skt) :
        Protocol(skt) {}



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
/*
PlayersIniDTO ClientProtocol::recvPlayersIni() {
    int operationType = recvANumberByte();
    std::vector<PlayerDTO> playersIniDTO;
    if (operationType == PLAYERS_INITIAL){
        size_t numberPlayers = recvANumberByte();
        for(size_t i = 0; i < numberPlayers; i++){
            playersIniDTO.push_back( recvAPlayerDTO());
        }
        return PlayersIniDTO(playersIniDTO);
    }
    std::cerr << "Error en el recvPlayersIni";
    return PlayersIniDTO(playersIniDTO);
}

PlayerDTO ClientProtocol::recvAPlayerDTO() {
    int operationType = recvANumberByte();
    std::vector<WormDTO> wormsBelongPlayer;
    if (operationType == PLAYER){
        size_t idPlayer = recvANumberByte();
        size_t numberWorms = recvANumberByte();
        for(size_t i = 0; i < numberWorms; i++){
            wormsBelongPlayer.push_back( recvWormIni() );
        }
        return PlayerDTO(idPlayer, wormsBelongPlayer);
    }
    std::cerr << "Error en el recvAPlayerDTO";
    return PlayerDTO(0,wormsBelongPlayer);
}

WormDTO ClientProtocol::recvWormIni() {
    int operationType = recvANumberByte();
    if (operationType == WORM){
        size_t idWorm = recvANumberByte();
        size_t positionX =  recvNum2Bytes();
        size_t positionY = recvNum2Bytes();
        return WormDTO(idWorm, positionX, positionY);
    }
    std::cerr << "Error en el recvWormIni";
    return WormDTO(0, 0, 0);
}

*/

void ClientProtocol::sendCommandDTO(const CommandDTO& commandDto) {
    unsigned int operationType = commandDto.getOperationType();
    unsigned int commandType = commandDto.getTypeCommand();
    std::cout << operationType << std::endl;
    std::cout << commandType << std::endl;
    sendANumberByte(operationType);
    sendANumberByte(commandType);
}

SnapShot ClientProtocol::recvASnapShot() {
    SnapShot aSnapShot;
    std::vector<WormDTO> vecWormsDTO;
    size_t operationType = recvANumberByte();
    if (operationType == SNAP_SHOT){
        size_t numbersWorms = recvANumberByte();
        for(size_t i = 0; i < numbersWorms; i++){
            vecWormsDTO.push_back(recvAWormDTO());
        }
        aSnapShot.setWormsDTO(vecWormsDTO);
    }
    return aSnapShot;
}

WormDTO ClientProtocol::recvAWormDTO() {
    WormDTO aWormDTO;
    int operationType = recvANumberByte();
    if (operationType == OperationType::WORM){
        size_t positionX = recvNum2Bytes();
        size_t positionY = recvNum2Bytes();
        size_t hpWorm = recvANumberByte();
        size_t directionLook = recvANumberByte();
        Direction aDirection;
        if( directionLook == Direction::LEFT){
            aDirection = Direction::LEFT;
        } else if (directionLook == Direction::RIGHT){
            aDirection  = Direction::RIGHT;
        }
        MoveWorm aMoveWorm;
        size_t moveWorm = recvANumberByte();
        if (moveWorm == MoveWorm::WALKING){
            aMoveWorm = MoveWorm::WALKING;
        } else if (moveWorm == MoveWorm::JUMPING){
            aMoveWorm = MoveWorm::JUMPING;
        } else if (moveWorm == MoveWorm::STANDING){
            aMoveWorm = MoveWorm::STANDING;
        }
        TypeFocusWorm typeFocusWorm;
        size_t focusWorm = recvANumberByte();
        if( focusWorm == TypeFocusWorm::FOCUS ){
            typeFocusWorm = TypeFocusWorm::FOCUS;
        } else if (focusWorm == TypeFocusWorm::NO_FOCUS){
            typeFocusWorm = TypeFocusWorm::NO_FOCUS;
        }
        WormDTO otherWormDTO(positionX, positionY, hpWorm, aDirection, typeFocusWorm, aMoveWorm);
        return otherWormDTO;
    }
    return aWormDTO;
}


