//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include "GamesProtected.h"
#include "../../../Common/DTO/RoomDTO.h"

#define SUCCESS 1
#define ERROR 2


GamesProtected::GamesProtected() {

}


int
GamesProtected::createGameAndAddPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer = ERROR;
    if(games.count(response.getGameName()) > 0){  // Si el nombre de la partida ya existe devolvemos ERROR
        return answer;
    }
    games[response.getGameName()] = new Engine(response); // Si el nombre no existe creamos un engine y unimos al jugador.
    answer = games[response.getGameName()]->addClient(sktPeer, playerName);
    return answer;
}

int GamesProtected::addPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    return games[response.getGameName()]->addClient(sktPeer, playerName);
}

void GamesProtected::printRooms() {
    std::unique_lock<std::mutex> lck(mtx);
    std::map<std::string, Engine*>::iterator it;
    for (it = games.begin(); it != games.end(); ++it){
        std::cout << "Room : " << it->first;
        it->second->print();
    }

}

std::vector<std::string> GamesProtected::getScenarios() {
    std::unique_lock<std::mutex> lck(mtx); // operacion de solo lectura no debe habe problemas.
    std::vector<std::string> scenariosHard {"VigaMania", "Jaula Maldita", "Vigas 10"};
    return scenariosHard;
}

std::vector<RoomDTO> GamesProtected::getAvailableRooms() {
    std::unique_lock<std::mutex> lck(mtx);
    std::vector<RoomDTO> roomsGames;
    std::map<std::string, Engine*>::iterator it;

    for (it = games.begin(); it != games.end(); ++it){
        if(it->second->isAvailable()){
            roomsGames.push_back(it->second->getRoomDTO());
        }
    }
    return roomsGames;
}


