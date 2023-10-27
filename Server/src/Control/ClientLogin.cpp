//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include "ClientLogin.h"
#define OPERATION_SUCCESS 1
#define OPERATION_ERROR 2

ClientLogin::ClientLogin(Socket socket, GamesProtected &aGames) : sktPeer(std::move(socket)) , games(aGames), isRunning(true),
                                                                  serverProtocol(sktPeer) {

}
// Arrancamos el protocolo inicial los primeros bytes del juego :
void ClientLogin::run() {
    try{
        InitialStateDTO initialState = serverProtocol.recvInitialStateDTO();
        int operationType = initialState.getOperationType();
        if( operationType == SCENARIO_LIST_REQUEST ){// scenarios harcodeado los nombre debemos acarlos de un archivo @Anita.
            ResolverInitialDTO resolverInitialDto(RESPONSE_INITIAL_CREATE_GAME, games.getScenarios());
            serverProtocol.sendResolverInitialDTO(resolverInitialDto);
        } else if ( operationType == ROOM_LIST_REQUEST ){
            ResolverInitialDTO resolverInitialDto(RESPONSE_INITIAL_JOIN_GAME, games.getAvailableRooms());
            serverProtocol.sendResolverInitialDTO(resolverInitialDto);
        }
        while( isRunning){
            ResponseInitialStateDTO response = serverProtocol.recvReponseInitialStateDTO();
            execute(response, initialState.getPlayerName());
        }
    }catch ( const std::exception& e){
        std::cerr << "[Client Login] Run:  Exception: " <<  e.what() ;
    }
    isRunning = false;
}



bool ClientLogin::isDead() const {
    return !isRunning;
}

void ClientLogin::stop() {
    isRunning = false;
    sktPeer.totalClosure();
}

void ClientLogin::execute(const ResponseInitialStateDTO &response, const std::string &playerName) {
    int operationType = response.getOperationType(), answer;

    if( operationType == FINAL_CREATE_GAME){
        answer = games.createGameAndAddPlayer(response, sktPeer, playerName);         //pasamos el skt por referenciia y si salio todo ok sera movido sino no se movera.
        if(answer == OPERATION_SUCCESS){
            ResolverInitialDTO aNewResolverInitial(RESPONSE_FINAL_CREATE_GAME, OPERATION_SUCCESS);
            serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
            isRunning = false;
        } else if ( answer == OPERATION_ERROR ) {
            ResolverInitialDTO aNewResolverInitial(RESPONSE_FINAL_CREATE_GAME, OPERATION_ERROR);
            serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
        }
    } else if ( operationType == FINAL_JOIN_GAME){
        answer = games.addPlayer(response, sktPeer, playerName);
        if (answer == OPERATION_SUCCESS){
            isRunning = false;
            ResolverInitialDTO responseJoinGame(RESPONSE_FINAL_JOIN_GAME, OPERATION_SUCCESS);
            serverProtocol.sendResolverInitialDTO(responseJoinGame);
        }
        else if (answer == OPERATION_ERROR){
            ResolverInitialDTO responseJoinGame(RESPONSE_FINAL_JOIN_GAME, OPERATION_ERROR);
            RoomDTO roomDto("JuegosLocos", "VigaMania", 1, 4);                     // cargammos los rooms disponibles y enviamos.
            RoomDTO roomDtoDos("Batalla final", "Jaula Maldita", 2, 4);
            std::vector<RoomDTO> gameRooms {roomDto, roomDtoDos};
            responseJoinGame.setGameRooms(gameRooms);
            serverProtocol.sendResolverInitialDTO(responseJoinGame);
        }
    }
}



