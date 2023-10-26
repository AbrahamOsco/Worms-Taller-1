//
// Created by abraham on 25/10/23.
//

#include "GamesProtected.h"
#define SUCCESS 1
#define ERROR 1


GamesProtected::GamesProtected() {

}


int GamesProtected::createGameAndJoinPlayer(const std::string &gameName, Socket peerJugador, const size_t &idJugador) {
    std::unique_lock<std::mutex> lck(mtx);
    int answer = ERROR;
    if(games.count(gameName) > 0){  // Si el nombre de la partida ya existe devolvemos ERROR
        return answer;
    }
    //games[gameName] = new Engine(gameName );

    // Creamos la "partida" (engine).


    return 0;
}

