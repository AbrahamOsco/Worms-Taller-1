//
// Created by abraham on 19/10/23.
//

#ifndef WORMS_TALLER_1_SERVER_H
#define WORMS_TALLER_1_SERVER_H


#include "../../../Common/common_socket.h"

class Server {
private:
    Socket aceptador;
public:
    Server(const char *serviceName);

    int run();
};


#endif //WORMS_TALLER_1_SERVER_H
