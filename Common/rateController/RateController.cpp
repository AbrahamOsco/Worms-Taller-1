//
// Created by riclui on 15/11/23.
//

#include "RateController.h"

RateController::RateController(int rate1) : rate(rate1) {
    this->start();
}

RateController::~RateController() {
}

void RateController::start() {
    t1 = std::chrono::steady_clock::now();
    t2 = t1;
    rest = 0;
    behind = 0;
    lost = 0;
    it = 1;
}

int RateController::getRateLoop() {
    return it;
}

void RateController::finish() {
    it = 0;
    t2 = std::chrono::steady_clock::now();
    diff = t2 - t1;
    rest = rate - std::ceil(diff.count());
    if (rest < 0) {
        behind = -rest;
        lost = rate + (behind - behind % rate);
        rest = rate - behind % rate;
        t1 += std::chrono::milliseconds(lost);
        it += std::floor(lost / rate);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(rest));
    t1 += std::chrono::milliseconds(rate);
    it += 1;
}

