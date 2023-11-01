#include "waiter.h"
#include "thread.h"
#include <unistd.h>
#include <iostream>
#include "../../../Common/Queue/Queue.h"
#include "../../src/protocol/ClientProtocol.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"

Waiter::Waiter(Socket* socket,Queue<ResolverInitialDTO>* queue){
    skt = socket;
    my_queue = queue;
}

void Waiter::run(){
    ClientProtocol protocol(*skt);
    ResolverInitialDTO respuesta;
    while (respuesta.getOperationType() == START_GAME){
        respuesta = protocol.recvResolverInitialDTO();
    }
    my_queue->push(respuesta);
}