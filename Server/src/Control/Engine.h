//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_ENGINE_H
#define WORMS_TALLER_1_ENGINE_H

#include <string>
#include <map>
#include <atomic>
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/Socket/Socket.h"
#include "../Model/Model.h"
#include "../../../Common/Thread/Thread.h"
#include "../../../Common/DTO/RoomDTO.h"
#include "EstablishedConnections.h"
#include "Command/Command.h"
#include "../../../Common/Queue/Queue.h"

/*
Entidad que sera el motor del juego en el server tendra el loop del box2d para iterar la fisica.
*/

class Engine : public Thread {
private:
    std::string nameGameRoom;
    std::string nameScenario;
    size_t numberPlayerReq;
    size_t currentPlayers;
    Model model;
    std::atomic<bool> keepTalking;
    Queue<Command*> commandsQueueNB;  // La queue para popear los comandos recibido por el cliente.
    Queue<WorldChangesDTO*> worldChangesBQ;   // La queue para pushear los update del mundo  para ser enviados al protocolo. Es pateado hasta ClientConnection es bloqueante
    EstablishedConnections connections;

    //std::map<size_t, ClientThread*> playersInRoom;
    // ACA AGREGAR UN MONITOR DE LOS CLIENTES CONECTADOAS A ESTA PARTIDA.

public:

    Engine(const ResponseInitialStateDTO &response);

    int addClient(Socket &socket, const std::string &playerName);

    bool isAvailable() const;

    void run() override;

    void stop();

    void print();

    RoomDTO getRoomDTO() const;

    void clearAll();
};


#endif //WORMS_TALLER_1_ENGINE_H
