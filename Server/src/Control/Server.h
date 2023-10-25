//
// Created by abraham on 19/10/23.
//

#ifndef WORMS_TALLER_1_SERVER_H
#define WORMS_TALLER_1_SERVER_H


#include "../../../Common/Socket/Socket.h"

class Server {
private:
    Socket sktAcceptor;
public:
    Server(const char *serviceName);

    int run();

    int runSingleThread();
};


#endif //WORMS_TALLER_1_SERVER_H
