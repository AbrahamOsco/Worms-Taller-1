#include "ServerProtocol.h"
#include "../../../Common/DTO/InitialStateDTO.h"

ServerProtocol::ServerProtocol(Socket& skt) :
        Protocol(skt){}

void ServerProtocol::sendWorm(const WormDTO &aWorm) {
    OperationType op = aWorm.getOperationType();
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
    if (operationType == OperationType::CREATE_GAME){
        aLobbyAnswer.setOperationType(OperationType::CREATE_GAME);
        std::string nameScenario = recvString();
        aLobbyAnswer.setSelectScenario(nameScenario);
    } else if (operationType == OperationType::JOIN_GAME){
        aLobbyAnswer.setOperationType(OperationType::JOIN_GAME);
    }
    return aLobbyAnswer;
}

InitialStateDTO ServerProtocol::recvInitialStateDTO() {
    InitialStateDTO initialStateDto;
    int operationType =  recvANumberByte();
    if (operationType == ERROR){
        return initialStateDto;
    }
    std::string playerName =  recvString();
    //Primero vemos el caso de creacion de un room.
    if(operationType == SCENARIO_LIST_REQUEST){
        initialStateDto.setOperationType(SCENARIO_LIST_REQUEST);
    } else if (operationType == ROOM_LIST_REQUEST){
        initialStateDto.setOperationType(ROOM_LIST_REQUEST);
    }
    initialStateDto.setPlayerName(playerName);
    return initialStateDto;
}

void ServerProtocol::sendResolverInitialDTO(const ResolverInitialDTO &resolverInitial) {
    int operationType =  resolverInitial.getOperationType();

    if( operationType == RESPONSE_INITIAL_CREATE_GAME ){     // Envio tipo de operacion, cantida de escenarios y el nombre de cada escenario.
        sendANumberByte(RESPONSE_INITIAL_CREATE_GAME);
        sendANumberByte(resolverInitial.getScenariosNames().size());
        for (const auto& aNameScenario : resolverInitial.getScenariosNames() ) {
            sendString(aNameScenario);
        }
    } else if ( operationType == RESPONSE_FINAL_CREATE_GAME ){    // Enviamos el tipo de operacion y el estado de la  respuesta.
        sendANumberByte(RESPONSE_FINAL_CREATE_GAME);
        sendANumberByte(resolverInitial.getStatusAnswer());
    } else if ( operationType == RESPONSE_INITIAL_JOIN_GAME ){  //  Enviamso el tipo de operacion, cantida de rooms y data de cada room.
        sendANumberByte(RESPONSE_INITIAL_JOIN_GAME);
        sendANumberByte(resolverInitial.getGameRooms().size());
        for (const auto& aRoomGame : resolverInitial.getGameRooms() ) {
            sendRoom(aRoomGame);
        }
    } else if ( operationType == RESPONSE_FINAL_JOIN_GAME ){
        sendANumberByte(RESPONSE_FINAL_JOIN_GAME);
        sendANumberByte(resolverInitial.getStatusAnswer());
        if ( resolverInitial.getStatusAnswer() == ERROR ){ // Si es error el tipo de status mandamos todos los rooms disponibles
            sendANumberByte(resolverInitial.getGameRooms().size());
            for (const auto& aRoomGame : resolverInitial.getGameRooms() ) {
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
    if (operationType == FINAL_CREATE_GAME){
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
    sendANumberByte(STAGE);
    sendANumberByte(stageDTO.getBeams().size());
    for(BeamDTO aBeamDTO : stageDTO.getBeams()){
        sendBeam(aBeamDTO);
    }
}

void ServerProtocol::sendBeam(const BeamDTO &beamDTO) {
    sendANumberByte(BEAM);
    sendANumberByte(beamDTO.getTypeBeam());
    sendANumberByte(beamDTO.getXCenter());
    sendANumberByte(beamDTO.getYCenter());
    sendANumberByte(beamDTO.getAngle());
    sendANumberByte(beamDTO.getLenghth());
    sendANumberByte(beamDTO.getHeight());
}

