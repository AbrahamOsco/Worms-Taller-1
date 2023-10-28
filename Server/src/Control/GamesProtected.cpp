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
        std::cerr << "[GamesProtected] Error No se creo la partida porque ya existe un nombre de esa partida\n";
        return answer;
    }
    games[response.getGameName()] = new Engine(response); // Si el nombre no existe creamos un engine y unimos al jugador.
    answer = games[response.getGameName()]->addClient(sktPeer, playerName);
    std::cerr << "[GamesProtected]: Se agrego al jugador " + playerName + " con exito a la partida : " + response.getGameName() + "\n";
    return answer;
}

int GamesProtected::addPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer =  games[response.getGameName()]->addClient(sktPeer, playerName);
    if(answer == SUCCESS){
        std::cerr << "[GamesProtected]: Se agrego al jugador " + playerName + " con exito a la partida : " + response.getGameName() + "\n";
    } else {
        std::cerr << "[GamesProtected]: ERROR No se agrego al jugador " + playerName + " a la partida : " + response.getGameName() + "\n";
    }
    return answer;
}

void GamesProtected::printRooms() {
    std::unique_lock<std::mutex> lck(mtx);
    std::map<std::string, Engine*>::iterator it;
    for (it = games.begin(); it != games.end(); ++it){
        std::cout << "Room : " << it->first << " |";
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


