//
// Created by abraham on 24/10/23.
//

#include "GameRoom.h"


GameRoom::GameRoom(const std::string &nameGameRoom, const std::string &nameScenario, const size_t &numberPlayerReq)
        : nameGameRoom(nameGameRoom), nameScenario(nameScenario), numberPlayerReq(numberPlayerReq), currentPlayers(0) {

}


void GameRoom::addPlayer(ClientThread* clientThr) {
    if(currentPlayers < numberPlayerReq ){
        playersInRoom[clientThr->getIdThread()] = clientThr;
        currentPlayers++;
    }
}

std::string GameRoom::getNameGameRoom() const {
    return nameGameRoom;
}



