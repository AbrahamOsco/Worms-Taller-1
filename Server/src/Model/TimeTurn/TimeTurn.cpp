//
// Created by abraham on 17/11/23.
//

#include "TimeTurn.h"

TimeTurn::TimeTurn() {
}

void TimeTurn::startTurn() {
    this->lastTime =  std::chrono::steady_clock::now();
}

bool TimeTurn::hasItBeenASecond() {
    this->currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedSeconds = currentTime - this->lastTime;
    return (elapsedSeconds.count() >= 1.0f);
}

void TimeTurn::updateTime() {
    lastTime = currentTime;
}
