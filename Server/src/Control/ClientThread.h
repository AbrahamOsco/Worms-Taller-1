//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_CLIENTTHREAD_H
#define WORMS_TALLER_1_CLIENTTHREAD_H

#include <cstddef>
#include <atomic>

#include "../../../Common/Socket/Socket.h"
#include "../../Common/Thread/Thread.h"
#include "ProtectedGameRooms.h"

class ClientThread : public Thread {
private:
    Socket sktPeer;                             // cppcheck-suppress unusedStructMember
    std::atomic<bool> keepTalking;           // cppcheck-suppress unusedStructMember
    std::atomic<bool> isAlive;               // cppcheck-suppress unusedStructMember
    size_t idThread;                         // cppcheck-suppress unusedStructMember
    ProtectedGameRooms &gameRooms;
    //MapQueuesProtected& mapQueuesProtected;  // cppcheck-suppress unusedStructMember
public:
    //  Constructor
    ClientThread(Socket socket, size_t i, ProtectedGameRooms &gameRooms);
    //  Pre: -.
    //  Post: Retorna true si el thread cliente deja de estar conectado false en caso opuesto.
    bool isDead() const;

    //  Pre: -.
    //  Post: Retorna true si el thread cliente deja de estar conectado false en caso opuesto.
    void kill();

    //  Pre: -.
    //  Post: Retorna el id del thread.
    size_t getIdThread() const;

    //  Pre: -.
    //  Post: Lanza los threads Recv y los thread sender respectivamente, espera a que termina y los
    //  joinea.
    virtual void run() override;

    //  Destructor
    ~ClientThread() = default;

};


#endif //WORMS_TALLER_1_CLIENTTHREAD_H
