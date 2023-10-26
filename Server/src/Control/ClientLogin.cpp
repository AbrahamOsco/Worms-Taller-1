//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include "ClientLogin.h"

ClientLogin::ClientLogin(Socket socket, GamesProtected &aGames) : sktPeer(std::move(socket)) , games(aGames), isRunning(true),
                                                                  serverProtocol(sktPeer) {

}

void ClientLogin::run() {
    try{
        InitialStateDTO initialState = serverProtocol.recvInitialStateDTO();
        while( isRunning){
            int operationType = initialState.getOperationType();
            if( operationType == SCENARIO_LIST_REQUEST ){
                std::vector<std::string > scenariosHard {"VigaMania", "Jaula Maldita", "Vigas 10"};    // scenarios harcodeado los nombre debemos acarlos de un archivo @Anita.
                ResolverInitialDTO resolverInitialDto(RESPONSE_INITIAL_CREATE_GAME, scenariosHard);
                serverProtocol.sendResolverInitialDTO(resolverInitialDto);
            } else if ( operationType == ROOM_LIST_REQUEST ){
                //RoomDTO roomDto("JuegosLocos");
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


