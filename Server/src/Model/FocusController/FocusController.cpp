//
// Created by abraham on 25/11/23.
//

#include <iostream>
#include <utility>
#include <vector>
#include "FocusController.h"

FocusController::FocusController(Players& players) : players(players), idPlayerCurrent(0),
                    idWormCurrent(0), currenWorm(nullptr) {
}

void FocusController::assignPlayerAndWormCurrent(const size_t& idPlayerCurrent, const size_t& idWormCurrent) {
    this->idPlayerCurrent = idPlayerCurrent;
    this->idWormCurrent = idWormCurrent;
    this->currenWorm = players.getCurrentPlayer().getCurrentWorm();
}

void FocusController::tryToChangeFocus() {
    std::vector<std::pair<size_t, size_t>> movingWorms;
    players.getMovingWorms(movingWorms);
    if (movingWorms.empty() || currenWorm->thereAreProjectiles() || currenWorm->hasTheTeleport()) {
        // si hay proyectiles o estamos usando el teleport -> No cambiamos el focus
        return;
    } else if (movingWorms.size() == 1 && (movingWorms.back().second == idWormCurrent)) {
        currenWorm->assignTypeFocus(FOCUS);
        return;
    }

    for (auto &pairIDPlayWorm : movingWorms) {
        if (pairIDPlayWorm.second != idWormCurrent) {
            players.assignTypeFocus(FOCUS, pairIDPlayWorm.first, pairIDPlayWorm.second);
            currenWorm->assignTypeFocus(NO_FOCUS);
        }
    }
}



