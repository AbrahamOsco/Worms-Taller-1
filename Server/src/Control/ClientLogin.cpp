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
        // HACER EL PROTOCOLO ACA.  y delegar en metodos.
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


