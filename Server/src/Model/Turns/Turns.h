//
// Created by abraham on 15/11/23.
//

#ifndef WORMS_TALLER_1_TURNS_H
#define WORMS_TALLER_1_TURNS_H

#include <string>
#include <memory>
#include <vector>
#include "../Players/Players.h"
#include "../../../../Common/DTO/TurnDTO.h"
#include "../Provision/Provision.h"
#include "../FocusController/FocusController.h"

class Turns {
 private:
    GameParameters gameParameters;
    Players& players;
    size_t idPlayerCurrent;
    std::string textTurn;
    int timeLeft;
    size_t idWormCurrent;
    bool damageRecognized;
    bool attackRecognized;
    int valueWind;
    TypeWind typeWind;
    b2World* world;
    std::vector<std::unique_ptr<Provision>> provisionBoxes;
    FocusController focusController;

 public:
    explicit Turns(Players &players, const GameParameters &parameters, b2World *world);

    void startATurn();


    void subtractTime();

    void tryEndTurn();

    TurnDTO getTurnDTO() const;

    int getTimeLeft() const;

    float getWindValueForPhysics();

    void addProvisionToWorld();

    void cleanProvisionsDestroyed();

    std::vector<ProvisionDTO> getVecProvisionDTO();

    void tryToChangeFocus();
};


#endif  // WORMS_TALLER_1_TURNS_H
