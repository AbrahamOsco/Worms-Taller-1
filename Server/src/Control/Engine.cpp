//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include <utility>
#include "Engine.h"
#include "../Protocol/ServerProtocol.h"
#define SUCCESS 1
#define ERROR 2


Engine::Engine(const ResponseInitialStateDTO &response) :
        nameGameRoom(response.getGameName()), nameScenario(response.getScenarioName()),
        numberPlayerReq(response.getPlayerRequired()), currentPlayers(0),
        world(b2Vec2(0.0f, gameParameters.getGravity())), model(response.getScenarioName(),
        world, gameParameters), keepTalking(false), startedGame(false), commandsQueueNB(UINT_MAX - 1),
        connections(commandsQueueNB) {
}

void Engine::sendStatusAnswer(Socket& sktPeer, const OperationType& operationType) {
    ResolverInitialDTO aNewResolverInitial(operationType, SUCCESS);
    ServerProtocol serverProtocol(sktPeer);
    serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
}

int Engine::addClient(Socket &socket, const std::string &playerName, const OperationType &aOperation) {
    int answer = ERROR;
    if ( this->currentPlayers < numberPlayerReq ) {
        model.addPlayer(playerName, currentPlayers);
        sendStatusAnswer(socket, aOperation);
        connections.addConnection(currentPlayers, std::move(socket));
        currentPlayers++;
        if (currentPlayers == numberPlayerReq) {
            keepTalking = true;
            startedGame = true;
            this->start();
        }
        answer = SUCCESS;
    }
    return answer;
}



void Engine::run() {
    try {
        std::cout  << "[Engine]: La partida  " + this->nameGameRoom + " En el scenario: " +
        this->nameScenario + " Con : " +  std::to_string(currentPlayers) +
        "/" + std::to_string(numberPlayerReq) + " Ha comenzado\n";
        StageDTO stageDto = model.startAndGetStageDTO();
        connections.start(stageDto);
        RateController frameRate(20);
        TimeTurn timeTurn;
        while (keepTalking) {
            if (model.onlyOnePlayerExits()) {
                break;
            }
            stepWorldAndExecuteCommand();
            pushUpdatesAndUpdateModel(timeTurn, frameRate);
        }
    } catch (std::exception &e) {
        std::cerr << "[Engine] Excepcion  :"  <<e.what() << "\n";
        this->connections.stop();
        this->model.destroyAllBodys();
        return;
    }
    executeLastCommand();
}

void Engine::executeLastCommand() {
    RateController frameRate(20);
    connections.pushVecEndGame(model.getVecEndGameDTO());
    while (keepTalking) {
        CommandDTO aCommanDTO;
        if (commandsQueueNB.try_pop(aCommanDTO)) {
            if (aCommanDTO.getTypeCommand() == CLOSE_GAME) {
                this->connections.stop();
                this->model.destroyAllBodys();
                keepTalking = false;
            }
        }
    }
}

void Engine::stepWorldAndExecuteCommand() {
    CommandDTO aCommanDTO;
    this->world.Step(gameParameters.getFPS(), gameParameters.getVelocityIterations(),
    gameParameters.getPositionIterations());
    if (commandsQueueNB.try_pop(aCommanDTO)) {
        this->model.execute(aCommanDTO, model.getTimeLeft());
    } else {
        this->model.tryAttackVariablePower();
    }
}

void Engine::pushUpdatesAndUpdateModel(TimeTurn& timeTurn, RateController& frameRate) {
    connections.pushSnapShot(model.getWormsDTO(), model.getPlayersDTO(), model.getVecWeaponsDTO(),
    model.getWeaponSightDTO(), model.getProjectilesDTO(), model.getTurnDTO(), model.getVecProvisionDTO());
    if (timeTurn.hasItBeenASecond()) {
        model.tryToChangeFocus();
        model.subtractTime();
        timeTurn.updateTime();
    }
    model.update();
    frameRate.finish();
}


bool Engine::isAvailable() const {
    return (currentPlayers < numberPlayerReq);
}

RoomDTO Engine::getRoomDTO() const {
    RoomDTO roomDTO;
    roomDTO.setGameName(this->nameGameRoom);
    roomDTO.setScenarioName(this->nameScenario);
    roomDTO.setPlayerRequired(this->numberPlayerReq);
    roomDTO.setPlayerCurent(this->currentPlayers);
    return roomDTO;
}

void Engine::stop() {
    keepTalking = false;
}


bool Engine::isGameStarted() const {
    return startedGame;
}
