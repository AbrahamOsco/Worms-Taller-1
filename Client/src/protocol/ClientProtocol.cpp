#include <iostream>
#include <string>
#include <vector>
#include "ClientProtocol.h"

#include "../../../Common/DTO/InitialStateDTO.h"
#include "../exception/ClosedServer.h"

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

    if (typeOperation == RESPONSE_INITIAL_CREATE_GAME) {
        size_t numberScenarios = recvANumberByte();
        std::vector<std::string> scenarioNames;
        for (size_t i = 0; i < numberScenarios ; i++) {
            scenarioNames.push_back(recvString());
        }
        resolverInitialDto.setOperationType(RESPONSE_INITIAL_CREATE_GAME);
        resolverInitialDto.setScenarioNames(scenarioNames);

        size_t sizeVecMaxWorms = recvANumberByte();
        std::vector<size_t> vecMaxNumberWorms;
        for (size_t i = 0; i < sizeVecMaxWorms; i++) {
            vecMaxNumberWorms.push_back(recvANumberByte());
        }
        resolverInitialDto.setVecMaxNumbersWorms(vecMaxNumberWorms);

    } else if ( typeOperation == RESPONSE_FINAL_CREATE_GAME ) {
        resolverInitialDto.setOperationType(RESPONSE_FINAL_CREATE_GAME);
        resolverInitialDto.setStatusAnswer(recvANumberByte());
    } else if (typeOperation == RESPONSE_INITIAL_JOIN_GAME) {
        resolverInitialDto.setOperationType(RESPONSE_INITIAL_JOIN_GAME);
        size_t numberRooms = recvANumberByte();
        std::vector<RoomDTO> gameRooms;
        for (size_t i = 0; i < numberRooms; i++) {
            gameRooms.push_back(recvRoom());
        }
        resolverInitialDto.setGameRooms(gameRooms);
    } else if (typeOperation == RESPONSE_FINAL_JOIN_GAME) {
        resolverInitialDto.setOperationType(RESPONSE_FINAL_JOIN_GAME);
        resolverInitialDto.setStatusAnswer(recvANumberByte());
        if (resolverInitialDto.getStatusAnswer() == ERROR) {
            // si es error recibimos los nuevos rooms disponibles.
            size_t numberRooms = recvANumberByte();
            std::vector<RoomDTO> gameRooms;
            for (size_t i = 0; i < numberRooms; i++) {
                gameRooms.push_back(recvRoom());
            }
            resolverInitialDto.setGameRooms(gameRooms);
        }
    } else if (typeOperation == START_GAME) {
        resolverInitialDto.setOperationType(START_GAME);
    }
    return resolverInitialDto;
}


RoomDTO ClientProtocol::recvRoom() {
    RoomDTO roomDto;
    int operationType = recvANumberByte();
    if (operationType == ROOM_GAME) {
        roomDto.setGameName(recvString());
        roomDto.setScenarioName(recvString());
        roomDto.setPlayerCurent(recvANumberByte());
        roomDto.setPlayerRequired(recvANumberByte());
    }
    return roomDto;
}

void ClientProtocol::sendResponseInitialStateDTO(const ResponseInitialStateDTO &responseInitial) {
    int operationType = responseInitial.getOperationType();
    if ( operationType == FINAL_CREATE_GAME ) {
        sendANumberByte(FINAL_CREATE_GAME);
        sendString(responseInitial.getGameName());
        sendString(responseInitial.getScenarioName());
        sendANumberByte(responseInitial.getPlayerRequired());
    } else if ( operationType == FINAL_JOIN_GAME ) {
        sendANumberByte(FINAL_JOIN_GAME);
        sendString(responseInitial.getGameName());
    }
}

StageDTO ClientProtocol::recvStageDTO() {
    StageDTO stageDto;
    size_t typeOperation = recvANumberByte();
    if (typeOperation == STAGE) {
        size_t numberBeams = recvANumberByte();
        std::vector<BeamDTO> beams;
        for (size_t i = 0 ; i < numberBeams; i++) {
            beams.push_back(recvBeamDTO());
        }
        stageDto.setBeams(beams);
        stageDto.setIdPlayer(recvANumberByte());
        stageDto.setPositionYWater(recvNum2Bytes());
        stageDto.setBackground(recvString());
    }
    // std::cout << "Se recibieron stage basuras\n";
    return stageDto;
}

BeamDTO ClientProtocol::recvBeamDTO() {
    BeamDTO beamDto;
    int operationType = recvANumberByte();
    if ( operationType == BEAM ) {
        TypeBeam aTypeBeam = static_cast<TypeBeam>(recvANumberByte());
        size_t xCenter = recvNum2Bytes();
        size_t yCenter = recvNum2Bytes();
        size_t angle = recvANumberByte();
        size_t length = recvANumberByte();
        size_t height = recvANumberByte();
        BeamDTO beamRecv(aTypeBeam, xCenter, yCenter, length, height, angle);
        return beamRecv;
    }
    std::cout << "Se recibieron beams basuras\n";
    return beamDto;
}
PlayersDTO ClientProtocol::recvPlayersDTO() {
    int operationType = recvANumberByte();
    std::vector<PlayerDTO> vecPlayerDTO;
    if (operationType == PLAYERS_TOTAL) {
        size_t numberPlayers = recvANumberByte();
        for (size_t i = 0; i < numberPlayers; i++) {
            vecPlayerDTO.push_back(recvAPlayerDTO());
        }
        return PlayersDTO(vecPlayerDTO);
    }
    return PlayersDTO(vecPlayerDTO);
}

PlayerDTO ClientProtocol::recvAPlayerDTO() {
    PlayerDTO aPlayerDto;
    int operationType = recvANumberByte();
    if (operationType == PLAYER) {
        size_t idPlayer = recvANumberByte();
        std::string namePlayer = recvString();
        TurnType aTurnType = static_cast<TurnType>(recvANumberByte());
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
    sendNum2Bytes(commandDto.getX());
    sendNum2Bytes(commandDto.getY());
}

SnapShot ClientProtocol::recvSnapShot() {
    std::vector<WormDTO> vecWormsDTO;
    std::vector<ProvisionDTO> vecProvisionDTO;
    int  operationType = recvANumberByte();
    if (operationType == CLOSED_CONNECTION) {
        throw ClosedServer();
    }
    if (operationType == SNAP_SHOT) {
        GameState typeSnapShot = static_cast<GameState>(recvANumberByte());
        if (typeSnapShot == GAME_PROGRESS) {
            size_t numbersWorms = recvANumberByte();
            for (size_t i = 0; i < numbersWorms; i++) {
                vecWormsDTO.push_back(recvAWormDTO());
            }
            PlayersDTO playersDto = recvPlayersDTO();
            WeaponsDTO weaponsDto = recvWeaponsDTO();
            WeaponSightDTO weaponSightDto = recvWeaponSightDTO();
            ProjectilesDTO projectilesDto = recvProjectilesDTO();
            TurnDTO turnDto = recvTurnDTO();
            size_t numberProvision = recvANumberByte();
            for (size_t i = 0; i < numberProvision; i++) {
                vecProvisionDTO.push_back(recvAProvisionDTO());
            }
            return SnapShot(vecWormsDTO, playersDto, weaponsDto, weaponSightDto,
                            projectilesDto, turnDto, vecProvisionDTO);
        } else if (typeSnapShot == GAME_END) {
            EndGameDTO endGameDto = recvEndGameDTO();
            return SnapShot(endGameDto);
        }
    }
    return SnapShot(vecWormsDTO, PlayersDTO(), WeaponsDTO(), WeaponSightDTO(),
                    ProjectilesDTO(), TurnDTO(), vecProvisionDTO);
}

ProvisionDTO ClientProtocol::recvAProvisionDTO() {
    int typeOperation = recvANumberByte();
    if (typeOperation == PROVISION_DTO) {
        size_t positionX = recvNum2Bytes();
        size_t positionY = recvNum2Bytes();
        TypeEffect typeEffect = static_cast<TypeEffect>(recvANumberByte());
        TypeContact typeContact = static_cast<TypeContact>(recvANumberByte());
        return ProvisionDTO(positionX, positionY, typeEffect, typeContact);
    }
    return ProvisionDTO();
}

EndGameDTO ClientProtocol::recvEndGameDTO() {
    int typeOperation =  recvANumberByte();
    if (typeOperation == END_DTO) {
        size_t idPlayer = recvANumberByte();
        TypeResult typeResult = static_cast<TypeResult>(recvANumberByte());
        return EndGameDTO(idPlayer, typeResult);
    }
    return EndGameDTO();
}

TurnDTO ClientProtocol::recvTurnDTO() {
    int typeOperation = recvANumberByte();
    if (typeOperation == TURN_DTO) {
        size_t idPlayerCurrent = recvANumberByte();
        std::string textTurn = recvString();
        size_t timeLeft = recvANumberByte();
        size_t valueWind = recvANumberByte();
        TypeWind typeWind = static_cast<TypeWind>(recvANumberByte());
        return TurnDTO(idPlayerCurrent, textTurn, timeLeft, valueWind, typeWind);
    }
    return TurnDTO(0, "0", 0, 0, WIND_LEFT);
}

ProjectilesDTO ClientProtocol::recvProjectilesDTO() {
    int typeOperation = recvANumberByte();
    std::vector<ProjectileDTO> vecProjectileDTO;
    if ( typeOperation == PROJECTILES_DTO ) {
        TypeShowProjectiles typeShow = static_cast<TypeShowProjectiles>(recvANumberByte());
        size_t numberProjectiles = recvANumberByte();
        for (size_t i = 0; i < numberProjectiles; i++) {
            vecProjectileDTO.push_back(recvAProjectileDTO());
        }
        return ProjectilesDTO(typeShow, vecProjectileDTO);
    }
    return ProjectilesDTO(NO_SHOW_PROJECTILES, vecProjectileDTO);
}

ProjectileDTO ClientProtocol::recvAProjectileDTO() {
    int operationType = recvANumberByte();
    if (operationType == OperationType::PROJECTILE_DTO) {
        TypeProjectil aTypeProj = static_cast<TypeProjectil>(recvANumberByte());
        size_t positionX = recvNum2Bytes();
        size_t postionY = recvNum2Bytes();
        TypeFocus typeFocus = static_cast<TypeFocus>(recvANumberByte());
        TypeExplode typeExplode = static_cast<TypeExplode>(recvANumberByte());
        return ProjectileDTO(aTypeProj, positionX, postionY, typeFocus, typeExplode);
    }
    return ProjectileDTO(NONE_PROJECTILE, 0, 0, NO_FOCUS, NO_EXPLODE);
}

WormDTO ClientProtocol::recvAWormDTO() {
    WormDTO aWormDTO;
    int operationType = recvANumberByte();
    if (operationType == OperationType::WORM) {
        size_t positionX = recvNum2Bytes();
        size_t positionY = recvNum2Bytes();
        size_t idPlayer = recvANumberByte();
        size_t hpWorm = recvANumberByte();
        Direction aDirection = static_cast<Direction>(recvANumberByte());
        MoveWorm aMoveWorm = static_cast<MoveWorm>(recvANumberByte());
        TypeFocus typeFocusWorm = static_cast<TypeFocus>(recvANumberByte());
        TypeWeapon typeWeapon = static_cast<TypeWeapon> (recvANumberByte());
        WormDTO otherWormDTO(positionX, positionY, idPlayer, hpWorm, aDirection, typeFocusWorm, aMoveWorm, typeWeapon);
        return otherWormDTO;
    }
    return aWormDTO;
}

WeaponsDTO ClientProtocol::recvWeaponsDTO() {
    WeaponsDTO weaponsDT0;
    std::vector<WeaponDTO> vecWeaponDTO;
    int operationType = recvANumberByte();
    size_t idPlayer = recvANumberByte();
    TypeWeapon typeWeaponCurrent = static_cast<TypeWeapon>(recvANumberByte());
    if (operationType == WEAPONS_TOTAL) {
        size_t numberWeapons = recvANumberByte();
        for (size_t i = 0; i < numberWeapons ; i++) {
            vecWeaponDTO.push_back(recvAWeaponDTO());
        }
        weaponsDT0.setIdPlayer(idPlayer);
        weaponsDT0.setWeaponCurrent(typeWeaponCurrent);
        weaponsDT0.setWeapons(vecWeaponDTO);
    }
    return weaponsDT0;
}

WeaponDTO ClientProtocol::recvAWeaponDTO() {
    WeaponDTO aWeaponDTO;
    int operationType = recvANumberByte();
    if (operationType == WEAPON) {
        TypeWeapon typeWeapon = static_cast<TypeWeapon>(recvANumberByte());
        TypeMunition typeMunition = static_cast<TypeMunition>(recvANumberByte());
        size_t munition = recvANumberByte();
        return WeaponDTO(typeWeapon, typeMunition, munition);
    }
    return aWeaponDTO;
}

WeaponSightDTO ClientProtocol::recvWeaponSightDTO() {
    int operationType = recvANumberByte();
    if (operationType == WEAPON_SIGHT) {
        TypeSight aTypeSight = static_cast<TypeSight>(recvANumberByte());
        size_t positionX = recvNum2Bytes();
        size_t positionY = recvNum2Bytes();
        return WeaponSightDTO(aTypeSight, positionX, positionY);
    }
    return WeaponSightDTO();
}

