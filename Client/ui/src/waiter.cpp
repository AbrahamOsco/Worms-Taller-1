#include "waiter.h"
#include "thread.h"
#include <unistd.h>
#include <iostream>
#include "../../../Common/Queue/Queue.h"
Waiter::Waiter(Socket* socket,Queue<int>* queue){
    skt = socket;
    my_queue = queue;
}

void Waiter::run(){
    uint8_t code = 1;
    bool closed = false;
    //skt->recvall(&code,1,&closed);
    sleep(10);
    my_queue->push((int) code);
}