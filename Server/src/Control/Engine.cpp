//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include "Engine.h"
#define SUCCESS 1
#define ERROR 2

Engine::Engine(const ResponseInitialStateDTO &response) :nameGameRoom( response.getGameName()) , nameScenario(response.getScenarioName()),
                                                        numberPlayerReq(response.getPlayerRequired()) {

}

// Retorna 1 si agrego con exito al jugador o retorna 2 Si hubo un ERROR.
int Engine::addClient(Socket &socket, const std::string &playerName) {
    int answer = ERROR;
    if( this->currentPlayers < numberPlayerReq ){
        model.addPlayer(playerName, currentPlayers);
        currentPlayers++;
        if (currentPlayers == numberPlayerReq){
            std::string estadoPartida = std::to_string(currentPlayers) + "/" + std::to_string(numberPlayerReq)  + " Ha comenzado\n";
            std::cout << "[Engine]: La partida  " + this->nameGameRoom  + " En el scenario: " + this->nameScenario + " Con : " + estadoPartida;
            this->start();
        }
        answer = SUCCESS;
    }
    return answer;
}

void Engine::run() {
    std::cout << "Lanzo el hilo Partida ahora esta corriendo el juego :D\n";

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
