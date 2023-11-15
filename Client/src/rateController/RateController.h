//
// Created by riclui on 15/11/23.
//

#ifndef WORMS_TALLER_1_RATECONTROLLER_H
#define WORMS_TALLER_1_RATECONTROLLER_H

#include <cmath>
#include <thread>
#include <chrono>

class RateController {
private:
    int rate;
    std::chrono::duration<float, std::milli> diff;
    int rest,lost,behind,it;

    std::chrono::steady_clock::time_point t1,t2;

public:
    RateController(int rate);

    void start();
    void stop();

    int getRateLoop();
    void finish();

    ~RateController();
};


#endif //WORMS_TALLER_1_RATECONTROLLER_H
