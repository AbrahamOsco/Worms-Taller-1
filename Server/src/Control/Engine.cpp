//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include "Engine.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/SnapShot.h"
#include "../../../Common/rateController/RateController.h"

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
        std::string estadoPartida =
                std::to_string(currentPlayers) + "/" + std::to_string(numberPlayerReq) + " Ha comenzado\n";
        std::cout << "[Engine]: La partida  " + this->nameGameRoom + " En el scenario: " + this->nameScenario +
                     " Con : " + estadoPartida;
        StageDTO stageDto = model.startAndGetStageDTO();
        connections.start(stageDto);
        RateController frameRate(20);
        frameRate.start();
        std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(); // lastTime para el contador del tiempo.

        while (keepTalking) {
            this->world.Step(gameParameters.getFPS(), gameParameters.getVelocityIterations(), gameParameters.getPositionIterations()); // Hacemos un step en el world.
            std::unique_ptr<CommandDTO> aCommanDTO;
            if (commandsQueueNB.move_try_pop(aCommanDTO)) {
                this->model.execute(aCommanDTO);
            } else {
                this->model.tryAttackVariablePower();
            }
            connections.pushSnapShot(model.getWormsDTO(), model.getPlayersDTO(), model.getVecWeaponsDTO(),
                                     model.getWeaponSightDTO(), model.getProjectilesDTO(), model.getTurnDTO());

            std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsedSeconds = currentTime - lastTime;
            if (elapsedSeconds.count() >= 1.0f) {
                model.subtractTime();
                lastTime = currentTime;
            }

            model.update();
            frameRate.finish();
        }
        this->connections.stop();
        this->clearAll(); // Limpiamos las queues.
        std::cerr << "[Engine]:run Terminando la ejecucion del juego \n";
    } catch (std::exception &e) {
        std::cerr << "[Engine]:run Excepcion en el run  \n";
        std::cerr << e.what() << "\n";
    }
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
