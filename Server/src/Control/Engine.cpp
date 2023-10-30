//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include "Engine.h"
#include "../Protocol/ServerProtocol.h"

#define SUCCESS 1
#define ERROR 2

Engine::Engine(const ResponseInitialStateDTO &response) : nameGameRoom( response.getGameName()) , nameScenario(response.getScenarioName()),
                                                          numberPlayerReq(response.getPlayerRequired()), keepTalking(true),
                                                          commandsQueueNB(UINT_MAX - 1), worldChangesNB(UINT_MAX - 1), connections(commandsQueueNB, worldChangesNB) {
}

// Retorna 1 si agrego con exito al jugador o retorna 2 Si hubo un ERROR.
int Engine::addClient(Socket &socket, const std::string &playerName) {
    int answer = ERROR;
    if( this->currentPlayers < numberPlayerReq ){
        model.addPlayer(playerName, currentPlayers);
        connections.addConnection(currentPlayers, std::move(socket));
        currentPlayers++;
        if (currentPlayers == numberPlayerReq){
            this->start();
        }
        answer = SUCCESS;
    }
    return answer;
}


void Engine::run() {
    std::string estadoPartida = std::to_string(currentPlayers) + "/" + std::to_string(numberPlayerReq)  + " Ha comenzado\n";
    std::cout << "[Engine]: La partida  " + this->nameGameRoom  + " En el scenario: " + this->nameScenario + " Con : " + estadoPartida;
    connections.start(model.getStageDTO()); // Le digo a todos las conexiones de esta partida  "start". es decir que lanzen los hilos sender y receiv cada conexion.
    connections.pushUpdate();  //pusheamos actualizaciones
    while(keepTalking){

    }
    this->connections.stop();
    this->clearAll(); // Limpiamos las queues.
    std::cerr << "[Engine]:run Terminando la ejecucion del juego \n";
}




void Engine::print() {
    std::cout << "Scenario: " << nameScenario << "|" << currentPlayers << "/" << numberPlayerReq << "\n";
}

bool Engine::isAvailable() const {
    return (currentPlayers < numberPlayerReq);
}

RoomDTO Engine::getRoomDTO() const {
    RoomDTO roomDTO;
    roomDTO.setGameName(this->nameGameRoom);
    roomDTO.setScenarioName(this->nameScenario);
    roomDTO.setPlayerRequired(this->numberPlayerReq);
    roomDTO.setPlayerCurent(this->currentPlayers);
    return roomDTO;
}

void Engine::stop() {
    keepTalking = false;
}

void Engine::clearAll() {
    // Limpiaremos las queeus aca?
}
