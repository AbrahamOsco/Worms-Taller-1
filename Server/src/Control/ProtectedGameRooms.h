//
// Created by abraham on 24/10/23.
//

#ifndef WORMS_TALLER_1_PROTECTEDGAMEROOMS_H
#define WORMS_TALLER_1_PROTECTEDGAMEROOMS_H

#include <mutex>
#include "GameRoom.h"
#include "ClientThread.h"

class ProtectedGameRooms {

private:
    std::map<std::string, GameRoom*> dicGameRooms;
    std::mutex mtx;

public:
    ProtectedGameRooms();

    void addGameRoomAndPlayer(const std::string &nameGameRoom, const std::string &nameScenario, const size_t &numberPlayerReq,
                              ClientThread *clientThread);


    void addPlayer(const std::string& nameGameRoom, ClientThread* clientThread);


};


#endif //WORMS_TALLER_1_PROTECTEDGAMEROOMS_H
