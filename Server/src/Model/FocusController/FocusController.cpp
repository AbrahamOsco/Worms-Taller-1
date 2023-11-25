//
// Created by abraham on 25/11/23.
//

#include <iostream>
#include "FocusController.h"

FocusController::FocusController(Players& players) : players(players) {
}

void FocusController::assignPlayerAndWormCurrent(const size_t& idPlayerCurrent, const size_t& idWormCurrent){
    this->idPlayerCurrent =idPlayerCurrent;
    this->idWormCurrent = idWormCurrent;
    this->currenWorm = players.getCurrentPlayer().getCurrentWorm();
}

void FocusController::tryToChangeFocus() {
    std::vector<std::pair<size_t, size_t>> movingWorms;
    players.getMovingWorms(movingWorms);
    if (movingWorms.empty() or currenWorm->thereAreProjectiles() or currenWorm->hasTheTeleport()) { // si hay proyectiles o estamos usando el teleport -> No cambiamos el focus
        return;
    } else if (movingWorms.size() == 1 and (movingWorms.back().second == idWormCurrent)) {
        currenWorm->assignTypeFocus(FOCUS);
        return;
    }

    for (auto &pairIDPlayWorm: movingWorms) {
        if (pairIDPlayWorm.second != idWormCurrent) {
            players.assignTypeFocus(FOCUS, pairIDPlayWorm.first, pairIDPlayWorm.second);
            currenWorm->assignTypeFocus(NO_FOCUS);
        }
    }
}



