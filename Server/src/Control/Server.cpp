//
// Created by abraham on 19/10/23.
//

#include "Server.h"
#include "ServerProtocol.h"

Server::Server(const char *serviceName) : sktAcceptor(Socket(serviceName)) {

}

int Server::run() {

}

int Server::runSingleThread(){
    Socket peer = sktAcceptor.accept();
    ServerProtocol serverProtocol(sktAcceptor);
    while(serverProtocol.isAvailable()){

    }
    return 0;
}