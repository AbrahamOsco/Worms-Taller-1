#ifndef WAITER_H
#define WAITER_H
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "thread.h"
#include "socket.h"
class Waiter: public Thread{
    private:
    Queue<ResolverInitialDTO>* my_queue;
    Socket* skt;
    
    public:
    Waiter(Socket* socket,Queue<ResolverInitialDTO>* queue);
    void run() override;
};
#endif