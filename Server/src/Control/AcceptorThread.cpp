//
// Created by abraham on 23/10/23.
//

#include <iostream>
#include "AcceptorThread.h"
#include "ClientLogin.h"


AcceptorThread::AcceptorThread(Socket &sktAccept, GamesProtected &aGames) : sktAccept(sktAccept), keepAcepting(true), games(aGames)  {}


void AcceptorThread::run() {
    try {
        while (keepAcepting) {
            addNewClient();
            cleanDeadClients();
        }
    } catch (const std::exception& e) {
        killAllClients();
    } catch (...) {
        std::cerr << "Unknown error\n";
    }
}



void AcceptorThread::addNewClient() {
    Socket sktPeer = sktAccept.accept();
    std::cout << "[AcceptorThread] : Se conecto un nuevo cliente\n";
    ClientLogin* aClientLogin = new ClientLogin(std::move(sktPeer), games);
    clientsLogin.emplace_back(aClientLogin);
    aClientLogin->start();
    //ClientThread* thrCliente = new ClientThread(std::move(sktPeer), nuevoId, games);
    //thrCliente->start();
    //clientes.push_back(thrCliente);
    /*
    Queue<AnswerDTO>* unaCola = new Queue<AnswerDTO>;
    mapQueuesProtected.addNewQueue(nuevoId, unaCola);
    idActual++;
    */

}

void AcceptorThread::cleanDeadClients() {
    clientsLogin.remove_if([this](ClientLogin* aClientLogin) {
        if (aClientLogin->isDead()) {
            aClientLogin->join();
            delete aClientLogin;
            return true;
        }
        return false;
    });
}

void AcceptorThread::killAllClients() {
    for (auto& unCliente: clientsLogin) {
        unCliente->stop();
        unCliente->join();
        delete unCliente;
    }
    clientsLogin.clear();
}


AcceptorThread::~AcceptorThread() {}

void AcceptorThread::stop() {
    keepAcepting = false;
    sktAccept.totalClosure();
}

