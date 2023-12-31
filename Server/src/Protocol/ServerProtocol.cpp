#include <iostream>
#include <string>
#include "ServerProtocol.h"
#include "../../../Common/DTO/InitialStateDTO.h"
#include "../../../Common/DTO/PlayerDTO.h"
#include "../../../Common/DTO/EndGameDTO.h"

ServerProtocol::ServerProtocol(Socket& skt) :
        Protocol(skt) {}

InitialStateDTO ServerProtocol::recvInitialStateDTO() {
    InitialStateDTO initialStateDto;
    int operationType =  recvANumberByte();
    if (operationType == BYTE_DISCONNECT) {
        return initialStateDto;
    }
    std::string playerName =  recvString();
    // Primero vemos el caso de creacion de un room.
    if (operationType == SCENARIO_LIST_REQUEST) {
        initialStateDto.setOperationType(SCENARIO_LIST_REQUEST);
    } else if (operationType == ROOM_LIST_REQUEST) {
        initialStateDto.setOperationType(ROOM_LIST_REQUEST);
    }
    initialStateDto.setPlayerName(playerName);
    return initialStateDto;
}

void ServerProtocol::sendResolverInitialDTO(const ResolverInitialDTO &resolverInitial) {
    int operationType =  resolverInitial.getOperationType();

    if ( operationType == RESPONSE_INITIAL_CREATE_GAME ) {
        // Envio tipo de operacion, cantida de escenarios y el nombre de cada escenario.
        sendANumberByte(RESPONSE_INITIAL_CREATE_GAME);
        sendANumberByte(resolverInitial.getScenariosNames().size());
        for (const auto& aNameScenario : resolverInitial.getScenariosNames()) {
            sendString(aNameScenario);
        }
        sendANumberByte(resolverInitial.getVecMaxNumbersWorms().size());
        for (const auto& aMaxNumberWorm : resolverInitial.getVecMaxNumbersWorms()) {
            sendANumberByte(aMaxNumberWorm);
        }
    } else if ( operationType == RESPONSE_FINAL_CREATE_GAME ) {
        // Enviamos el tipo de operacion y el estado de la  respuesta.
        sendANumberByte(RESPONSE_FINAL_CREATE_GAME);
        sendANumberByte(resolverInitial.getStatusAnswer());
    } else if ( operationType == RESPONSE_INITIAL_JOIN_GAME ) {
        //  Enviamso el tipo de operacion, cantida de rooms y data de cada room.
        sendANumberByte(RESPONSE_INITIAL_JOIN_GAME);
        sendANumberByte(resolverInitial.getGameRooms().size());
        for (const auto& aRoomGame : resolverInitial.getGameRooms()) {
            sendRoom(aRoomGame);
        }
    } else if ( operationType == RESPONSE_FINAL_JOIN_GAME ) {
        sendANumberByte(RESPONSE_FINAL_JOIN_GAME);
        sendANumberByte(resolverInitial.getStatusAnswer());
        if ( resolverInitial.getStatusAnswer() == STATUS_ERROR ) {
            // Si es error el tipo de status mandamos todos los rooms disponibles
            sendANumberByte(resolverInitial.getGameRooms().size());
            for (const auto& aRoomGame : resolverInitial.getGameRooms()) {
                sendRoom(aRoomGame);
            }
        }
    }
}

void ServerProtocol::sendRoom(const RoomDTO &aRoomDTO) {
    // enviamos toda la data del ROOM.
    sendANumberByte(aRoomDTO.getOperationType());
    sendString(aRoomDTO.getGameName());
    sendString(aRoomDTO.getScenarioName());
    sendANumberByte(aRoomDTO.getPlayerCurrent());
    sendANumberByte(aRoomDTO.getPlayerRequired());
}

ResponseInitialStateDTO ServerProtocol::recvReponseInitialStateDTO() {
    ResponseInitialStateDTO responseInitialStateDto;
    int operationType = recvANumberByte();
    if (operationType == FINAL_CREATE_GAME) {
        responseInitialStateDto.setOperationType(FINAL_CREATE_GAME);
        responseInitialStateDto.setGameName(recvString());
        responseInitialStateDto.setScenarioName(recvString());
        responseInitialStateDto.setPlayerRequired(recvANumberByte());
    } else if (operationType == FINAL_JOIN_GAME) {
        responseInitialStateDto.setOperationType(FINAL_JOIN_GAME);
        responseInitialStateDto.setGameName(recvString());
    }
    return responseInitialStateDto;
}

void ServerProtocol::sendStage(const StageDTO &stageDTO) {
    sendANumberByte(stageDTO.getOperationType());
    sendANumberByte(stageDTO.getBeams().size());
    for (BeamDTO aBeamDTO : stageDTO.getBeams()) {
        sendBeamDTO(aBeamDTO);
    }
    sendANumberByte(stageDTO.getIdPlayer());
    sendNum2Bytes(stageDTO.getPositionYWater());
    sendString(stageDTO.getBackground());
}

void ServerProtocol::sendBeamDTO(const BeamDTO &beamDTO) {
    sendANumberByte(beamDTO.getOperationType());
    sendANumberByte(beamDTO.getTypeBeam());
    sendNum2Bytes(beamDTO.getXCenter());
    sendNum2Bytes(beamDTO.getYCenter());
    sendANumberByte(beamDTO.getAngle());
    sendANumberByte(beamDTO.getLenghth());
    sendANumberByte(beamDTO.getHeight());
}

void ServerProtocol::sendPlayersDTO(const PlayersDTO &aPlayersDTO) {
    sendANumberByte(aPlayersDTO.getOperationType());
    sendANumberByte(aPlayersDTO.getPlayersDTO().size());
    for (const auto& aPlayer : aPlayersDTO.getPlayersDTO()) {
        sendAPlayerDTO(aPlayer);
    }
}

void ServerProtocol::sendAPlayerDTO(const PlayerDTO &playerDTO) {
    sendANumberByte(playerDTO.getOperationType());
    sendANumberByte(playerDTO.getIdPlayer());
    sendString(playerDTO.getNamePlayer());
    sendANumberByte(playerDTO.getTurnType());
    sendNum2Bytes(playerDTO.getTotalHpWorms());
}

CommandDTO ServerProtocol::recvCommandDTO() {
    CommandDTO commandDto;
    int operationType = recvANumberByte();
    if (operationType == COMMAND) {
        TypeCommand commandType = static_cast<TypeCommand>(recvANumberByte());
        commandDto.setTypeCommand(commandType);
        int x = recvNum2Bytes();
        int y = recvNum2Bytes();
        commandDto.setX(x);
        commandDto.setY(y);
    }
    return commandDto;
}

void ServerProtocol::sendSnapShot(const std::unique_ptr<SnapShot> &aSnapShot) {
    sendANumberByte(aSnapShot->getOperationType());
    sendANumberByte(aSnapShot->getTypeSnapShot());
    if (aSnapShot->getTypeSnapShot() == GAME_PROGRESS) {
        sendANumberByte(aSnapShot->getWormsDto().size());
        for (const auto& aWormDTO : aSnapShot->getWormsDto()) {
            sendAWormDTO(aWormDTO);
        }
        sendPlayersDTO(aSnapShot->getPlayersDto());

        sendWeaponsDTO(aSnapShot->getWeaponsDto());

        sendWeaponSightDTO(aSnapShot->getWeaponSightDto());

        sendProjectilesDTO(aSnapShot->getProjectilesDto());

        sendTurnDTO(aSnapShot->getTurnDto());

        sendANumberByte(aSnapShot->getVecProvisionDto().size());
        for (auto& aProvision : aSnapShot->getVecProvisionDto()) {
            sendAProvisionDTO(aProvision);
        }
    } else if (aSnapShot->getTypeSnapShot() == GAME_END) {
        sendEndGameDTO(aSnapShot->getEndGameDto());
    }
}

void ServerProtocol::sendAProvisionDTO(const ProvisionDTO& provisionDto) {
    sendANumberByte(provisionDto.getOperationType());
    sendNum2Bytes(provisionDto.getPositionX());
    sendNum2Bytes(provisionDto.getPositionY());
    sendANumberByte(provisionDto.getTypeEffect());
    sendANumberByte(provisionDto.getTypeContact());
}

void ServerProtocol::sendEndGameDTO(const EndGameDTO& endGameDto) {
    sendANumberByte(endGameDto.getOperationType());
    sendANumberByte(endGameDto.getIdPlayer());
    sendANumberByte(endGameDto.getTypeResult());
}

void ServerProtocol::sendTurnDTO(const TurnDTO& aTurnDTO) {
    sendANumberByte(aTurnDTO.getOperationType());
    sendANumberByte(aTurnDTO.getIdPlayerCurrent());
    sendString(aTurnDTO.getTextTurn());
    sendANumberByte(aTurnDTO.getTimeLeft());
    sendANumberByte(aTurnDTO.getValueWind());
    sendANumberByte(aTurnDTO.getTypeWind());
}


void ServerProtocol::sendProjectilesDTO(const ProjectilesDTO& projectilesDto) {
    sendANumberByte(projectilesDto.getOperationType());
    sendANumberByte(projectilesDto.getTypeShowProjectiles());
    sendANumberByte(projectilesDto.getProjectilesDto().size());
    for (auto& aProjectil : projectilesDto.getProjectilesDto()) {
        sendAProjectileDTO(aProjectil);
    }
}

void ServerProtocol::sendAProjectileDTO(const ProjectileDTO& aProjectilDTO) {
    sendANumberByte(aProjectilDTO.getOperationType());
    sendANumberByte(aProjectilDTO.getTypeProjectil());
    sendNum2Bytes(aProjectilDTO.getPositionX());
    sendNum2Bytes(aProjectilDTO.getPositionY());
    sendANumberByte(aProjectilDTO.getTypeFocus());
    sendANumberByte(aProjectilDTO.getTypeExplode());
}

void ServerProtocol::sendAWormDTO(const WormDTO &aWormDTO) {
    sendANumberByte(aWormDTO.getOperationType());
    sendNum2Bytes(aWormDTO.getPositionX());
    sendNum2Bytes(aWormDTO.getPositionY());
    sendANumberByte(aWormDTO.getIdPlayer());
    sendANumberByte(aWormDTO.getHpWorm());
    sendANumberByte(aWormDTO.getDirectionLook());
    sendANumberByte(aWormDTO.getMoveWorm());
    sendANumberByte(aWormDTO.getTypeFocus());
    sendANumberByte(aWormDTO.getWeaponCurrent());
}

void ServerProtocol::sendWeaponsDTO(const WeaponsDTO &weapons) {
    sendANumberByte(weapons.getOperationType());
    sendANumberByte(weapons.getIdPlayer());
    sendANumberByte(weapons.getWeaponCurrent());
    sendANumberByte(weapons.getWeapons().size());
    for (auto& aWeapon : weapons.getWeapons()) {
        sendAWeaponDTO(aWeapon);
    }
}

void ServerProtocol::sendAWeaponDTO(const WeaponDTO &aWeapon) {
    sendANumberByte(aWeapon.getOperationType());
    sendANumberByte(aWeapon.getTypeWeapon());
    sendANumberByte(aWeapon.getTypeMunition());
    sendANumberByte(aWeapon.getMunition());
}

void ServerProtocol::sendWeaponSightDTO(const WeaponSightDTO &weaponSightDto) {
    sendANumberByte(weaponSightDto.getOperationType());
    sendANumberByte(weaponSightDto.getTypeSight());
    sendNum2Bytes(weaponSightDto.getPositionXSight());
    sendNum2Bytes(weaponSightDto.getPositionYSight());
}

