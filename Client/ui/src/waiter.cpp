#include "../include/waiter.h"
#include <unistd.h>
#include <iostream>
#include "../../../Common/Thread/Thread.h"
#include "../../../Common/Queue/Queue.h"
#include "../../src/protocol/ClientProtocol.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"

Waiter::Waiter(Socket* socket, Queue<ResolverInitialDTO>* queue) {
    skt = socket;
    my_queue = queue;
}

void Waiter::run() {
    ClientProtocol protocol(*skt);
    bool closed = false;
    uint8_t read = 0;
    ResolverInitialDTO respuesta;
    while (read != 1 && !closed) {
        skt->recvall(&read, 1, &closed);
    }
    if (read == START_GAME) {
        respuesta.setOperationType(START_GAME);
    }
    if (closed) {
        respuesta.setOperationType(END_DTO);
    }
    my_queue->push(respuesta);
}
