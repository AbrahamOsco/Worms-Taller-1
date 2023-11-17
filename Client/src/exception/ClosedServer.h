//
// Created by riclui on 17/11/23.
//

#ifndef WORMS_TALLER_1_CLOSEDSERVER_H
#define WORMS_TALLER_1_CLOSEDSERVER_H

#include <stdexcept>

struct ClosedServer : public std::runtime_error {
    ClosedServer(): std::runtime_error("The server is closed") {}
};


#endif //WORMS_TALLER_1_CLOSEDSERVER_H
