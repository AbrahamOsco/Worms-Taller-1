//
// Created by abraham on 23/10/23.
//

#include <iostream>
#include <utility>
#include "AcceptorThread.h"
#include "ClientLogin.h"


AcceptorThread::AcceptorThread(Socket &sktAccept, GamesProtected &aGames) : sktAccept(sktAccept),
                keepAcepting(true), games(aGames)  {}


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
    std::unique_ptr<ClientLogin> unCliente{new ClientLogin(std::move(sktPeer), games)};
    unCliente->start();
    clientsLogin.push_back(std::move(unCliente));
}

void AcceptorThread::cleanDeadClients() {
    clientsLogin.remove_if([this](const std::unique_ptr<ClientLogin>& aClientLogin) {
        if (aClientLogin->isDead()) {
            aClientLogin->join();
            return true;
        }
        return false;
    });
}

void AcceptorThread::killAllClients() {
    for (auto& unCliente : clientsLogin) {
        unCliente->stop();
        unCliente->join();
    }
    clientsLogin.clear();
}


AcceptorThread::~AcceptorThread() {}

void AcceptorThread::stop() {
    keepAcepting = false;
    sktAccept.totalClosure();
}

