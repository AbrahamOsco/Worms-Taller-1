//
// Created by abraham on 24/10/23.
//

#include "ProtectedGameRooms.h"

ProtectedGameRooms::ProtectedGameRooms() {}

void ProtectedGameRooms::addGameRoomAndPlayer(const std::string &nameGameRoom, const std::string &nameScenario,
                                     const size_t &numberPlayerReq, ClientThread *clientThread ) {
    std::unique_lock<std::mutex> lck(mtx);
    GameRoom* newGameRoom = new GameRoom(nameGameRoom, nameScenario, numberPlayerReq);
    dicGameRooms[nameGameRoom] = newGameRoom;
    dicGameRooms[nameGameRoom]->addPlayer(clientThread);
}

void ProtectedGameRooms::addPlayer(const std::string &nameGameRoom, ClientThread *clientThread) {
    std::unique_lock<std::mutex> lck(mtx);
    dicGameRooms[nameGameRoom]->addPlayer(clientThread);
}




