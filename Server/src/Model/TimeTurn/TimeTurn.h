//
// Created by abraham on 17/11/23.
//

#ifndef WORMS_TALLER_1_TIMETURN_H
#define WORMS_TALLER_1_TIMETURN_H


#include <chrono>

class TimeTurn {
 private:
    std::chrono::steady_clock::time_point lastTime;
    std::chrono::steady_clock::time_point currentTime;
 public:
    TimeTurn();

    void startTurn();

    bool hasItBeenASecond();

    void updateTime();
};


#endif  // WORMS_TALLER_1_TIMETURN_H
