//
// Created by abraham on 25/10/23.
//

#ifndef WORMS_TALLER_1_ENGINE_H
#define WORMS_TALLER_1_ENGINE_H

#include <string>
#include <map>
#include <atomic>
#include <memory>
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../../Common/Socket/Socket.h"
#include "../Model/ModelGame/Model.h"
#include "../../../Common/DTO/RoomDTO.h"
#include "EstablishedConnections.h"
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/SnapShot.h"
#include "../../../Common/Thread/Thread.h"
#include "../../../Common/DTO/CommandDTO.h"
#include "../Model/TimeTurn/TimeTurn.h"
#include "../../../Common/rateController/RateController.h"

/*
Entidad que sera el motor del juego en el server tendra el loop del box2d para iterar la fisica.
*/

class Engine : public Thread {
 private:
    GameParameters gameParameters;
    std::string nameGameRoom;
    std::string nameScenario;
    size_t numberPlayerReq;
    size_t currentPlayers;
    b2World world;
    Model model;
    std::atomic<bool> keepTalking;
    Queue<std::unique_ptr<CommandDTO>> commandsQueueNB;
    // La queue para popear los comandos recibido por el cliente.
    // Solo tenemos una queue para popear comandos. y N queures para enviar.
    EstablishedConnections connections;
    void sendStatusAnswer(Socket &sktPeer, const OperationType &operationType);

 public:
    explicit Engine(const ResponseInitialStateDTO &response);

    int addClient(Socket &socket, const std::string &playerName, const OperationType &aOperation);

    bool isAvailable() const;

    void run() override;

    void stop();

    void print();

    RoomDTO getRoomDTO() const;

    void stepWorldAndExecuteCommand();

    void pushUpdatesAndUpdateModel(TimeTurn &timeTurn, RateController &frameRate);

    void executeLastCommand();
};


#endif  // WORMS_TALLER_1_ENGINE_H
