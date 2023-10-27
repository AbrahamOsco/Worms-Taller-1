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

/*
Entidad que sera el motor del juego en el server tendra el loop del box2d para iterar la fisica.
*/

class Engine {
private:
    std::string nameGameRoom;
    std::string nameScenario;
    size_t numberPlayerReq;
    size_t currentPlayers;
    std::atomic<bool> startedGame;
    Model model;
    //std::map<size_t, ClientThread*> playersInRoom;
    // ACA AGREGAR UN MONITOR DE LOS CLIENTES CONECTADOAS A ESTA PARTIDA.

public:

    Engine(const ResponseInitialStateDTO &response);

    int addClient(Socket &socket, const std::string &playerName);

    void start();
};


#endif //WORMS_TALLER_1_ENGINE_H
