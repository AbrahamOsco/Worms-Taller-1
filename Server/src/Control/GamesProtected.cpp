//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include "GamesProtected.h"
#include "../../../Common/DTO/RoomDTO.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "../Protocol/ServerProtocol.h"
#include "../Model/YamlParser/YamlParser.h"

#define SUCCESS 1
#define ERROR 2


GamesProtected::GamesProtected() {
    YamlParser::getScenarioAndMaxWorms(nameScenarios, maxNumbersWorms);
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
    // detalle, aca podes devolver una lista para que se imprima fuera del Games asi no bloqueas todo. Y cuidado con imprimir por cout, aunque este protegido por este mutex, no se usa en algun otro hilo en algun lugar?
    // como es para debuging no deberia ser un problema igual, pero para tener en cuenta
    std::map<std::string, std::unique_ptr<Engine>>::iterator it;
    for (it = games.begin(); it != games.end(); ++it){
        std::cout << "Room : " << it->first << " |";
        it->second->print();
    }

}

std::vector<std::string> GamesProtected::getScenarios() {
    std::unique_lock<std::mutex> lck(mtx); // operacion de solo lectura no debe habe problemas.
    return nameScenarios;
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
// hacemos join a todos los engine que fueron creado.
void GamesProtected::stop() {
    for(auto& Agames : games){
        Agames.second->stop();
        Agames.second->join();
    }
}

std::vector<std::size_t> GamesProtected::getMaxNumbersWorms() {
    std::unique_lock<std::mutex> lck(mtx); // operacion de solo lectura no debe habe problemas.
    return this->maxNumbersWorms;
}



