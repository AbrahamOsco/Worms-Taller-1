//
// Created by abraham on 25/10/23.
//

#include "Engine.h"
#define SUCCESS 1
#define ERROR 2

Engine::Engine(const ResponseInitialStateDTO &response) :nameGameRoom( response.getGameName()) , nameScenario(response.getScenarioName()),
                                                        numberPlayerReq(response.getPlayerRequired()), startedGame(false) {

}

int Engine::addClient(Socket &socket, const std::string &playerName) {
    int answer = ERROR;
    if( this->currentPlayers < numberPlayerReq ){
        model.addPlayer(playerName, currentPlayers);
        currentPlayers++;
        if (currentPlayers == numberPlayerReq){
            this->start();
        }
    }
    return 0;

}

void Engine::start() {

}
