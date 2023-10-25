//
// Created by abraham on 23/10/23.
//

#include <iostream>
#include "AcceptorThread.h"


AcceptorThread::AcceptorThread(Socket &sktAccept) : sktAccept(sktAccept), keepAcepting(true) {}


void AcceptorThread::run() {
    try {
        size_t idActual = 0;
        while (keepAcepting) {
            addNewClient(idActual);
            cleanDeadClients();
        }
    } catch (const std::exception& e) {
        killAllClients();
    } catch (...) {
        std::cerr << "Unknown error\n";
    }
}



void AcceptorThread::addNewClient(size_t& idActual) {
    size_t nuevoId = idActual;
    Socket sktPeer = sktAccept.accept();
    ClientThread* thrCliente = new ClientThread(std::move(sktPeer), nuevoId, gameRooms);
    thrCliente->start();
    clientes.push_back(thrCliente);

    /*
    Queue<AnswerDTO>* unaCola = new Queue<AnswerDTO>;
    mapQueuesProtected.addNewQueue(nuevoId, unaCola);
    idActual++;
    */

}

void AcceptorThread::cleanDeadClients() {
    clientes.remove_if([this](ClientThread* unCliente) {
        if (unCliente->isDead()) {
            unCliente->join();
            delete unCliente;
            return true;
        }
        return false;
    });
}

void AcceptorThread::killAllClients() {
    for (auto& unCliente: clientes) {
        unCliente->kill();
        unCliente->join();
        delete unCliente;
    }
    clientes.clear();
}


AcceptorThread::~AcceptorThread() {}

void AcceptorThread::stop() {
    keepAcepting = false;
    sktAccept.totalClosure();
}
