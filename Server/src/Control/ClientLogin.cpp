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

void ClientLogin::run() {
    try{
        InitialStateDTO initialState = serverProtocol.recvInitialStateDTO();
        int operationType = initialState.getOperationType();
        if( operationType == SCENARIO_LIST_REQUEST ){
            std::vector<std::string > scenariosHard {"VigaMania", "Jaula Maldita", "Vigas 10"};    // scenarios harcodeado los nombre debemos acarlos de un archivo @Anita.
            ResolverInitialDTO resolverInitialDto(RESPONSE_INITIAL_CREATE_GAME, scenariosHard);
            serverProtocol.sendResolverInitialDTO(resolverInitialDto);
        } else if ( operationType == ROOM_LIST_REQUEST ){
            RoomDTO roomDto("JuegosLocos", "VigaMania", 1, 4);
            RoomDTO roomDtoDos("Batalla final", "Jaula Maldita", 2, 4);
            RoomDTO roomDtoTres("Batalla final", "Vigas 10", 2, 5);
            std::vector<RoomDTO> gameRooms {roomDto, roomDtoDos, roomDtoTres};
            ResolverInitialDTO resolverInitialDto(RESPONSE_INITIAL_JOIN_GAME, gameRooms);
            serverProtocol.sendResolverInitialDTO(resolverInitialDto);
        }
        while( isRunning){
            ResponseInitialStateDTO response = serverProtocol.recvReponseInitialStateDTO();
            int operationType = response.getOperationType();
            if( operationType == FINAL_CREATE_GAME){
                int answer = games.createGameAndJoinPlayer(response, sktPeer, initialState.getPlayerName());
                //probar pasar el socket por movimiento y si no es asignado verlo en un caso de prueba.
                if(answer == OPERATION_SUCCESS){
                    // Me guardo los valores y mando el OK.
                    ResolverInitialDTO aNewResolverInitial(RESPONSE_FINAL_CREATE_GAME, OPERATION_SUCCESS);
                    serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
                    isRunning = false;
                } else if ( answer == OPERATION_ERROR ) {
                    ResolverInitialDTO aNewResolverInitial(RESPONSE_FINAL_CREATE_GAME, OPERATION_ERROR);
                    serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
                }
            } else if ( operationType == FINAL_JOIN_GAME){
                // actualizo al nuevo jugador guardo el peer esta ok.
                isRunning = false;
            }
        }

    }catch ( const std::exception& e){
        std::cerr << "Cerrando el socket todo OK " <<  e.what() ;
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


