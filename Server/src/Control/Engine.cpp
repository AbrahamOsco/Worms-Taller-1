//
// Created by abraham on 25/10/23.
//

#include <iostream>
#include <memory>
#include "Engine.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/SnapShot.h"
#define VELOCITY_ITERATIONS 6
#define POSITION_TIERATIONS 2
#define SUCCESS 1
#define ERROR 2
#define GRAVEDAD -10.0f

Engine::Engine(const ResponseInitialStateDTO &response) : nameGameRoom( response.getGameName()) , nameScenario(response.getScenarioName()),
                                                          numberPlayerReq(response.getPlayerRequired()), currentPlayers(0), world(b2Vec2(0.0f, gameParameters.getGravity())),
                                                          model(response.getScenarioName(), world, gameParameters), keepTalking(true), commandsQueueNB(UINT_MAX - 1),
                                                          connections(commandsQueueNB) {
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
    std::string estadoPartida = std::to_string(currentPlayers) + "/" + std::to_string(numberPlayerReq)  + " Ha comenzado\n";
    std::cout << "[Engine]: La partida  " + this->nameGameRoom  + " En el scenario: " + this->nameScenario + " Con : " + estadoPartida;
    model.start();
    connections.start(model.getStageDTO());
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now(), t2,t3;
    std::chrono::duration<double> frameTime{}, sleepTime{}, timeUsed{}, target(gameParameters.getFPS()), sleepAdjustSeconds(0.0);

    while(keepTalking){
        t1 = std::chrono::steady_clock::now();
        this->world.Step(gameParameters.getFPS(), gameParameters.getVelocityIterations(), gameParameters.getPositionIterations()); // Hacemos un step en el world.
        std::unique_ptr<CommandDTO> aCommanDTO;
        if (commandsQueueNB.move_try_pop(aCommanDTO)){
            this->model.execute(aCommanDTO);
        }
        connections.pushSnapShot(model.getWormsDTO());
        this->model.updateStateWorms();
        /*
        if(model.getWormsDTO().back().getMoveWorm() == STANDING){
            std::cout << "Quieto\n";
        } else if (model.getWormsDTO().back().getMoveWorm() == WALKING){
            std::cout << "Caminando\n";
        } else if (model.getWormsDTO().back().getMoveWorm() == JUMPING){
            std::cout << "Saltando \n";
        }
         */
        adjustFPS(target, t1, t2, t3, timeUsed, sleepTime, frameTime, sleepAdjustSeconds);
    }

    this->connections.stop();
    this->clearAll(); // Limpiamos las queues.
    std::cerr << "[Engine]:run Terminando la ejecucion del juego \n";
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

void Engine::adjustFPS(const std::chrono::duration<double> &target, std::chrono::steady_clock::time_point &t1, std::chrono::steady_clock::time_point &t2,
                       std::chrono::steady_clock::time_point &t3, std::chrono::duration<double> &timeUsed,
                       std::chrono::duration<double> &sleepTime, std::chrono::duration<double> &frameTime,
                       std::chrono::duration<double> &sleepAdjustSeconds) {
    t2 = std::chrono::steady_clock::now();
    timeUsed = t2 - t1;
    sleepTime = (target - timeUsed) + sleepAdjustSeconds;
    if (sleepTime > std::chrono::duration<double>(0) ){
        std::this_thread::sleep_for(sleepTime);
    }
    t3 = std::chrono::steady_clock::now();
    frameTime = t3 - t1;
    sleepAdjustSeconds = std::chrono::duration<double>(0.9 * sleepAdjustSeconds.count()) + std::chrono::duration<double>(0.1 * (target - frameTime).count());
}

