//
// Created by abraham on 28/10/23.
//

#include <iostream>
#include <utility>
#include "ClientConnection.h"
#include "../Protocol/ServerProtocol.h"
#include "../../../Common/DTO/PlayersDTO.h"
#include "../../../Common/DTO/ProjectilesDTO.h"
#include "../../../Common/DTO/TurnDTO.h"

// commandsQueueNB(UINT_MAX - 1)
ClientConnection::ClientConnection(const size_t &idPlayer, Socket aSktPeer,
        Queue<std::unique_ptr<CommandDTO>> &aCommandQueueNB) :
        idPlayer(idPlayer), sktPeer(std::move(aSktPeer)), commandQueueNB(aCommandQueueNB),
        snapShotQueueB(std::make_unique<Queue<std::unique_ptr<SnapShot>>>(UINT_MAX -1)) {
}


void ClientConnection::start(StageDTO &stageDTO) {  // Lanzo los threads sender y receiver
    // Aca envio el byte START_GAME y el stage completo antes de lanzar los thread receiver y sender.
    ServerProtocol serverProtocol(sktPeer);
    serverProtocol.sendANumberByte(START_GAME);
    stageDTO.setIdPlayer(this->idPlayer);
    serverProtocol.sendStage(stageDTO);
    receiver = std::thread(&ClientConnection::runReceiver, this);
    sender = std::thread(&ClientConnection::runSender, this);
}

void ClientConnection::join() {
    std::cerr << " [Thread Client]: Se entra a joinear los threads sender y receiver de : " << idPlayer << "\n";
    sender.join();
    std::cerr << " [Thread Client]: Join thread Sender "<< idPlayer << "\n";
    receiver.join();
    std::cerr << " [Thread Client]: Join thread Receiver" << idPlayer << "\n";
}

// enviamos snapShots al cliente (actualizaciones del mundo)
void ClientConnection::runSender() {
    try {
        ServerProtocol serverProtocol(sktPeer);
        std::unique_ptr<SnapShot> aSnapShot = nullptr;
        while ( (aSnapShot = snapShotQueueB->move_pop()) ) {
            serverProtocol.sendSnapShot(aSnapShot);
        }
    }catch (const std::exception& e ) {
        std::cerr << " [Thread Sender]: Excpecion catcheada: "<< idPlayer << "" << e.what() <<
        "Se procede a cerrar el socket peer \n";
        sktPeer.totalClosure();
        std::cerr << " [Thread Sender]: Se cerro el socket peer. "<< idPlayer << " Termino Thread Sender \n";
    }
}

void ClientConnection::runReceiver() {
    try {
        ServerProtocol serverProtocol(sktPeer);
        while (serverProtocol.isAvailable()) {
            std::unique_ptr<CommandDTO> aCommandDTO = std::make_unique<CommandDTO>(serverProtocol.recvCommandDTO());
            commandQueueNB.move_try_push(std::move(aCommandDTO));  // usamos una cola no bloqueante es -> try_push
        }
        std::cerr<< "[Thread Receiver]  id: "<< idPlayer <<
        "  Detecto cierre del socket asi que se hace el close de CommandQueue\n";
        commandQueueNB.close();
        // snapShotQueueB->close();
        std::cerr << "[Thread Receiver] "<< idPlayer << "   Termino thread receiver \n";
    }catch(const std::exception& e ) {
        // Si entro aca es porque otro cliente se desconecto y necesitamos cerrar todos los clientes
        std::cerr << "[Thread Receiver] Se cerro la queue de un cliente que estaba dispuesto a recibir mensajes" <<
        idPlayer << " Pero otro cliente se desconecto\n";
    }
}

void ClientConnection::stop() {
    std::cout << " [Thread cliente]  " << idPlayer << " STOP";
    if (sktPeer.isClosed()) {
        std::cout <<
        "[Thread cliente] el socket esta cerrado procedo a cerrar el snapShotQueue y hacerle un totalClouse al skt\n";
        snapShotQueueB->close();
        sktPeer.totalClosure();
    } else {
        // Solo tenemos una queue para popear comandos cierro la queue que envia snapshots
        snapShotQueueB->close();
        sktPeer.totalClosure();
    }
}

void ClientConnection::pushSnapShot(const std::vector<WormDTO> &vecWormsDTO, const PlayersDTO &playersDTO,
                                    const std::vector<WeaponsDTO> &vecWeaponsDTO, const WeaponSightDTO &weaponSightDTO,
                                    const ProjectilesDTO &projectilesDTO, TurnDTO turnDTO,
                                    const std::vector<ProvisionDTO> &vecProvisionDTO) {
    // aca en cada client connectio nago el unicast.
    WeaponsDTO selectWeaponsDTO;
    for (auto& aWeaponsDTO : vecWeaponsDTO) {
        if (aWeaponsDTO.getIdPlayer() == this->idPlayer) {
            selectWeaponsDTO = aWeaponsDTO;
            break;
        }
    }
    if (turnDTO.getIdPlayerCurrent() == this->idPlayer) {
        turnDTO.setTextTurn("Es tu turno");
    }
    std::unique_ptr<SnapShot> aSnapShot = std::make_unique<SnapShot>
    (vecWormsDTO, playersDTO, selectWeaponsDTO, weaponSightDTO, projectilesDTO, turnDTO, vecProvisionDTO);
    this->snapShotQueueB->move_push(std::move(aSnapShot));
}

void ClientConnection::pushEndGame(const std::vector<EndGameDTO> &vecEndGameDTO) {
    // unicast enviamos para cada jugador su correspondiente EndGameDTO para ver si perdio o gano el game.
    EndGameDTO selectEndGameDTO;
    for (auto& aEndGame : vecEndGameDTO) {
        if (aEndGame.getIdPlayer() == this->idPlayer) {
            selectEndGameDTO = aEndGame;
        }
    }
    std::unique_ptr<SnapShot> aSnapShot = std::make_unique<SnapShot>(selectEndGameDTO);
    this->snapShotQueueB->move_push(std::move(aSnapShot));
}


