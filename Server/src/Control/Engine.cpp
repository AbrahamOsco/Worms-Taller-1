//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include "Engine.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/SnapShot.h"
#include "../../../Common/rateController/RateController.h"
#include "../Model/TimeTurn/TimeTurn.h"

#define VELOCITY_ITERATIONS 6
#define POSITION_TIERATIONS 2
#define SUCCESS 1
#define ERROR 2
#define GRAVEDAD -10.0f

Engine::Engine(const ResponseInitialStateDTO &response) : nameGameRoom( response.getGameName()) , nameScenario(response.getScenarioName()),
                                                          numberPlayerReq(response.getPlayerRequired()), currentPlayers(0), world(b2Vec2(0.0f, gameParameters.getGravity())),
                                                          model(response.getScenarioName(), world, gameParameters), keepTalking(true), commandsQueueNB(UINT_MAX - 1),
                                                          connections(commandsQueueNB){
}

// Retorna 1 si agrego con exito al jugador o retorna 2 Si hubo un ERROR.
void Engine::sendStatusAnswer(Socket& sktPeer, const OperationType& operationType) {
    ResolverInitialDTO aNewResolverInitial(operationType, SUCCESS);
    ServerProtocol serverProtocol(sktPeer);
    serverProtocol.sendResolverInitialDTO(aNewResolverInitial);
}

int Engine::addClient(Socket &socket, const std::string &playerName, const OperationType &aOperation) {
    int answer = ERROR;
    if( this->currentPlayers < numberPlayerReq ){
        model.addPlayer(playerName, currentPlayers);
        sendStatusAnswer(socket, aOperation);
        connections.addConnection(currentPlayers, std::move(socket));
        currentPlayers++;
        if (currentPlayers == numberPlayerReq){
            this->start();
        }
        answer = SUCCESS;
    }
    return answer;
}

void Engine::run() {
    try{
        std::cout  << "[Engine]: La partida  " + this->nameGameRoom + " En el scenario: " + this->nameScenario + " Con : " +  std::to_string(currentPlayers) + "/" + std::to_string(numberPlayerReq) + " Ha comenzado\n";
        StageDTO stageDto = model.startAndGetStageDTO();
        connections.start(stageDto);
        RateController frameRate(20);// el start esta encapsulado en el constructor. OJO @
        TimeTurn timeTurn;  // en el constructor ya arranca el turn.
        while (keepTalking) {
            if(model.onlyOnePlayerExits()){
                keepTalking = false;
                break;
            }
            stepWorldAndExecuteCommand();
            pushUpdatesAndUpdateModel(timeTurn, frameRate);
        }
    } catch (std::exception &e) {
        std::cerr << "[Engine] Excpecion del tipo : :"  <<e.what() << "\n";
        this->connections.stop(); //[Por ahora lo comento no quiero cerrar todo quiero debgauar luego descomentar esto.
        return;
    }
    std::cerr<< "Felicidades acabaste el juego de forma exitosa !!! \n";
    this->connections.stop();
}

void Engine::stepWorldAndExecuteCommand() {
    std::unique_ptr<CommandDTO> aCommanDTO;
    this->world.Step(gameParameters.getFPS(), gameParameters.getVelocityIterations(), gameParameters.getPositionIterations()); // Hacemos un step en el world.
    if (commandsQueueNB.move_try_pop(aCommanDTO)) {
        this->model.execute(aCommanDTO, model.getTimeLeft());
    } else {
        this->model.tryAttackVariablePower();
    }
}

void Engine::pushUpdatesAndUpdateModel(TimeTurn& timeTurn, RateController& frameRate){
    connections.pushSnapShot(model.getWormsDTO(), model.getPlayersDTO(), model.getVecWeaponsDTO(), model.getWeaponSightDTO(), model.getProjectilesDTO(), model.getTurnDTO());
    if (timeTurn.hasItBeenASecond()) {
        model.subtractTime();
        timeTurn.updateTime();
    }
    model.update();
    frameRate.finish();
}


void Engine::print() {
    std::cout << "Scenario: " << nameScenario << "|" << currentPlayers << "/" << numberPlayerReq << "\n";
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

void Engine::clearAll() {
    // Limpiaremos las queeus aca?
}
