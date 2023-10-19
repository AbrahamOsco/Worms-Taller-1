//
// Created by abraham on 19/10/23.
//

#include "Server.h"

Server::Server(const char *serviceName) : aceptador(Socket(serviceName)) {

}

int Server::run() {

    return 0;
}
