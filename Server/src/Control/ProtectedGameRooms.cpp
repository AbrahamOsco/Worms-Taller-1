//
// Created by abraham on 24/10/23.
//

#include "ProtectedGameRooms.h"

ProtectedGameRooms::ProtectedGameRooms() {}

int ProtectedGameRooms::addGameRoomAndPlayer(const std::string &nameGameRoom, const std::string &nameScenario,
                                             const size_t &numberPlayerReq, ClientThread *clientThread ) {
    std::unique_lock<std::mutex> lck(mtx);
    if( dicGameRooms.count(nameGameRoom) > 0){
        return 1;
    }
    GameRoom* newGameRoom = new GameRoom(nameGameRoom, nameScenario, numberPlayerReq);
    dicGameRooms[nameGameRoom] = newGameRoom;
    dicGameRooms[nameGameRoom]->addPlayer(clientThread);
    return 0;
}

int ProtectedGameRooms::addPlayer(const std::string &nameGameRoom, ClientThread *clientThread) {
    std::unique_lock<std::mutex> lck(mtx);
    if( dicGameRooms.count(nameGameRoom) == 0){
        return 1;
    }
    dicGameRooms[nameGameRoom]->addPlayer(clientThread);
    return 0;
}




