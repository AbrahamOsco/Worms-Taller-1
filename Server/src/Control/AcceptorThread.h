//
// Created by abraham on 23/10/23.
//

#ifndef WORMS_TALLER_1_ACCEPTORTHREAD_H
#define WORMS_TALLER_1_ACCEPTORTHREAD_H

#include <cstddef>
#include <list>

#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Thread/Thread.h"
#include "GamesProtected.h"
#include "ClientLogin.h"
#include <memory>

class AcceptorThread : public Thread {
 private:
    Socket& sktAccept;                                          // cppcheck-suppress unusedStructMember
    std::list<std::unique_ptr<ClientLogin>> clientsLogin;      // cppcheck-suppress unusedStructMember
    std::atomic<bool> keepAcepting;
    GamesProtected& games;

    //  Pre: -
    //  Post: Limpia los clientes que se desconectaron del servidor y libera  sus recursos
    //  respectivos.
    void cleanDeadClients();

    //  Pre: -
    //  Post: Killea todos los  cliente guardados, porque el servidor esta por cerrar .
    void killAllClients();

    //  Pre: recibe el idActual del cliente
    //  Post: Agrega un nuevo cliente y le asigna su respectivo idCliente.
    void addNewClient();

 public:
    //  Constructor
    //  Recibe el socket por referencia y el gameProtected
    explicit AcceptorThread(Socket &sktAccept, GamesProtected &aGames);

    //  Pre: -
    //  Post: Acepta nuevos clientes, limpia clientes muertos, y si cierra el skt sktAcceptor killea
    //  los clientes.
    virtual void run() override;


    //  Destructor
    ~AcceptorThread();

    void stop();
};


#endif  // WORMS_TALLER_1_ACCEPTORTHREAD_H
