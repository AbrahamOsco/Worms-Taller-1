//
// Created by riclui on 31/10/23.
//

#ifndef WORMS_TALLER_1_GAME_H
#define WORMS_TALLER_1_GAME_H

#include <vector>
#include <string>
#include "../../../Common/Socket/Socket.h"
#include "../protocol/ClientProtocol.h"
#include "../gameObject/GameObject.h"
#include "../gameObject/beam/Beam.h"
#include "../gameObject/water/Water.h"

class Game {
 private:
    ClientProtocol m_protocol;
    std::vector<Beam> m_beams;
    std::string m_background;
    std::atomic<bool> m_running;
 public:
    explicit Game(Socket& skt);
    void loadMap();
    void run();
};


#endif  // WORMS_TALLER_1_GAME_H
