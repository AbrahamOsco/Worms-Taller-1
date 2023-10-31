#ifndef WAITER_H
#define WAITER_H
#include "../Common/Queue/Queue.h"
#include "thread.h"
#include "socket.h"
class Waiter: public Thread{
    private:
    Queue<int>* my_queue;
    Socket* skt;
    
    public:
    Waiter(Socket* socket,Queue<int>* queue);
    void run() override;
};
#endif