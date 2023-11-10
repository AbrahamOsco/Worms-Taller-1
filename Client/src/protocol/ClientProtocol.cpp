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
        TypeBeam aTypeBeam = static_cast<TypeBeam>( recvANumberByte() );
        size_t xCenter = recvNum2Bytes();
        size_t yCenter = recvNum2Bytes();
        size_t angle = recvANumberByte();
        size_t length = recvANumberByte();
        size_t height = recvANumberByte();
        BeamDTO beamRecv(aTypeBeam, xCenter, yCenter, length, height, angle);
        return beamRecv;
    }
    return beamDto;
}
PlayersDTO ClientProtocol::recvPlayersDTO() {
    int operationType = recvANumberByte();
    std::vector<PlayerDTO> vecPlayerDTO;
    if (operationType == PLAYERS_TOTAL){
        size_t numberPlayers = recvANumberByte();
        for(size_t i = 0; i < numberPlayers; i++){
            vecPlayerDTO.push_back( recvAPlayerDTO());
        }
        return PlayersDTO(vecPlayerDTO);
    }
    return PlayersDTO(vecPlayerDTO);
}

PlayerDTO ClientProtocol::recvAPlayerDTO() {
    PlayerDTO aPlayerDto;
    int operationType = recvANumberByte();
    if (operationType == PLAYER){
        size_t idPlayer = recvANumberByte();
        std::string namePlayer = recvString();
        TurnType aTurnType = static_cast<TurnType>( recvANumberByte());
        size_t totalHpWorms = recvNum2Bytes();

        return PlayerDTO(idPlayer, namePlayer, aTurnType, totalHpWorms);
    }
    return aPlayerDto;
}

void ClientProtocol::sendCommandDTO(const CommandDTO& commandDto) {
    unsigned int operationType = commandDto.getOperationType();
    unsigned int commandType = commandDto.getTypeCommand();
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
        // recibimos todos los playersDTO
        aSnapShot.setPlayersDto(recvPlayersDTO());

        //ahora recibimos a WeaponsDTO.
        aSnapShot.setWeaponsDto(recvWeaponsDTO());
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
        Direction aDirection = static_cast<Direction>( recvANumberByte() ) ;
        MoveWorm aMoveWorm = static_cast<MoveWorm>( recvANumberByte());
        TypeFocusWorm typeFocusWorm = static_cast<TypeFocusWorm>(  recvANumberByte());
        WormDTO otherWormDTO(positionX, positionY, hpWorm, aDirection, typeFocusWorm, aMoveWorm);
        return otherWormDTO;
    }
    return aWormDTO;
}

WeaponsDTO ClientProtocol::recvWeaponsDTO() {
    WeaponsDTO weaponsDT0;
    std::vector<WeaponDTO> vecWeaponDTO;
    int operationType = recvANumberByte();
    size_t idPlayer = recvANumberByte();
    if (operationType == WEAPONS_TOTAL){
        size_t numberWeapons = recvANumberByte();
        for(size_t i = 0; i < numberWeapons ; i++){
            vecWeaponDTO.push_back(recvAWeaponDTO());
        }
        weaponsDT0.setIdPlayer(idPlayer);
        weaponsDT0.setWeapons(vecWeaponDTO);
    }
    return weaponsDT0;
}

WeaponDTO ClientProtocol::recvAWeaponDTO() {
    WeaponDTO aWeaponDTO;
    int operationType = recvANumberByte();
    if (operationType == WEAPON){
        TypeWeapon typeWeapon = static_cast<TypeWeapon>( recvANumberByte());
        TypeMunition typeMunition = static_cast<TypeMunition>( recvANumberByte() );
        size_t munition = recvANumberByte();
        return WeaponDTO(typeWeapon, typeMunition, munition);
    }
    return aWeaponDTO;
}

