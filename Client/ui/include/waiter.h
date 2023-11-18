#ifndef WAITER_H  // NOLINT
#define WAITER_H
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../../../Common/Thread/Thread.h"
#include "../../../Common/Socket/Socket.h"
class Waiter: public Thread{
 private:
    Queue<ResolverInitialDTO>* my_queue;
    Socket* skt;
 public:
    Waiter(Socket* socket, Queue<ResolverInitialDTO>* queue);
    void run() override;
};
#endif  // NOLINT
