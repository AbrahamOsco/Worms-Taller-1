//
// Created by abraham on 25/11/23.
//

#ifndef WORMS_TALLER_1_FOCUSCONTROLLER_H
#define WORMS_TALLER_1_FOCUSCONTROLLER_H


#include "../Players/Players.h"

class FocusController {
 private:
    Players& players;
    size_t idPlayerCurrent;
    size_t idWormCurrent;
    Worm *currenWorm;

 public:
    explicit FocusController(Players& players);

    void assignPlayerAndWormCurrent(const size_t &idPlayerCurrent, const size_t &idWormCurrent);

    void tryToChangeFocus();
};


#endif  // WORMS_TALLER_1_FOCUSCONTROLLER_H
