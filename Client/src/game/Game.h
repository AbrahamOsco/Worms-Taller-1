//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_GAME_H
#define WORMS_TALLER_1_GAME_H

#include "../../../Common/Socket/Socket.h"
#include "../protocol/ClientProtocol.h"
#include "../gameObject/GameObject.h"
#include "../gameObject/beam/Beam.h"

class Game {
private:
    ClientProtocol m_protocol;

    std::vector<std::unique_ptr<Beam>> m_beams;
public:
    Game(Socket& skt);
    void loadMap();
    void run();
};


#endif //WORMS_TALLER_1_GAME_H
