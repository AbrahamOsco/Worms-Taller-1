//
// Created by abraham on 19/10/23.
//
#include <iostream>
#include "Server.h"
#include "../Protocol/ServerProtocol.h"

#include "AcceptorThread.h"

#define EXIT_KEY "q"


Server::Server(const char *serviceName) : sktAcceptor(Socket(serviceName)) {}

int Server::run() {
    AcceptorThread acceptorThread(sktAcceptor, games);
    acceptorThread.start();
    std::string input ;
    while ( input != EXIT_KEY) {
        std::cin >> input;
    }

    acceptorThread.stop();
    acceptorThread.join();
    return 0;
}

