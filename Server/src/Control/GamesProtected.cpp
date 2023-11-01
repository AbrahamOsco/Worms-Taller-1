//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include "GamesProtected.h"
#include "../../../Common/DTO/RoomDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../Protocol/ServerProtocol.h"

#define SUCCESS 1
#define ERROR 2


GamesProtected::GamesProtected() {
}


int GamesProtected::createGameAndAddPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer = ERROR;
    if(games.count(response.getGameName()) > 0){  // Si el nombre de la partida ya existe devolvemos ERROR
        std::cerr << "[GamesProtected] Error No se creo la partida porque ya existe un nombre de esa partida\n";
        return answer;
    }
    games[response.getGameName()] = std::make_unique<Engine>(response);    // Analogo a hacer std::unique_ptr<Engine>{new Engine(response)}.
    answer = games[response.getGameName()]->addClient(sktPeer, playerName, RESPONSE_FINAL_CREATE_GAME);
    std::cerr << "[GamesProtected]: Se unio: " + playerName + " con exito a la partida : " + response.getGameName() + "\n";
    return answer;
}

int GamesProtected::addPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer = games[response.getGameName()]->addClient(sktPeer, playerName, RESPONSE_FINAL_JOIN_GAME);
    if(answer == SUCCESS){
        std::cerr << "[GamesProtected]: Se unio: " + playerName + " con exito a la partida : " + response.getGameName() + "\n";
    } else {
        std::cerr << "[GamesProtected]: ERROR No se agrego al jugador " + playerName + " a la partida : " + response.getGameName() + "\n";
    }
    return answer;
}

void GamesProtected::printRooms() {
    std::unique_lock<std::mutex> lck(mtx);
    std::map<std::string, std::unique_ptr<Engine>>::iterator it;
    for (it = games.begin(); it != games.end(); ++it){
        std::cout << "Room : " << it->first << " |";
        it->second->print();
    }

}

std::vector<std::string> GamesProtected::getScenarios() {
    std::unique_lock<std::mutex> lck(mtx); // operacion de solo lectura no debe habe problemas.
    std::vector<std::string> scenariosHard;
    scenariosHard.emplace_back("Jaula maldita");
    scenariosHard.emplace_back("Vigamania");

    return scenariosHard;
}

std::vector<RoomDTO> GamesProtected::getAvailableRooms() {
    std::unique_lock<std::mutex> lck(mtx);
    std::vector<RoomDTO> roomsGames;
    std::map<std::string, std::unique_ptr<Engine>>::iterator it;

    for (it = games.begin(); it != games.end(); ++it){
        if(it->second->isAvailable()){
            roomsGames.push_back(it->second->getRoomDTO());
        }
    }
    return roomsGames;
}

void GamesProtected::stop() {
    // deterner todos los client connect ACA.
}



