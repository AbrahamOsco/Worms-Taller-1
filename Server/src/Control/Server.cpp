//
// Created by abraham on 19/10/23.
//
#include <iostream>
#include "Server.h"
#include "ServerProtocol.h"

#include "AcceptorThread.h"

#define EXIT_KEY 'q'

Server::Server(const char *serviceName) : sktAcceptor(Socket(serviceName)) {}

int Server::run() {
    AcceptorThread acceptorThread(sktAcceptor);
    acceptorThread.start();
    while (std::cin.get() != EXIT_KEY) {}
    sktAcceptor.totalClosure();
    acceptorThread.join();
    return 0;
}

int Server::runSingleThread(){
    Socket peer = sktAcceptor.accept();
    ServerProtocol serverProtocol(sktAcceptor);
    while(serverProtocol.isAvailable()){

    }
    return 0;
}