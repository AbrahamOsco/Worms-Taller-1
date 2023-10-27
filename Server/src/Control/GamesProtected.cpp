//
// Created by abraham on 25/10/23.
//

#include "GamesProtected.h"
#define SUCCESS 1
#define ERROR 2


GamesProtected::GamesProtected() {

}


int
GamesProtected::createGameAndJoinPlayer(const ResponseInitialStateDTO &response, Socket &sktPeer, const std::string &playerName) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer = ERROR;
    if(games.count(response.getGameName()) > 0){  // Si el nombre de la partida ya existe devolvemos ERROR
        return answer;
    }
    games[response.getGameName()] = new Engine(response);

    answer = games[response.getGameName()]->addClient(sktPeer, playerName);

    return answer;
}

