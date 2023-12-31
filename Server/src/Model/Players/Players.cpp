//
// Created by abraham on 31/10/23.
//

#include "Players.h"
#include "../../../GameParameters/GameParameters.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

Players::Players(const std::map<size_t, std::pair<float, float>> &idsAndPositionsWorms,
            const GameParameters& parameters)
        : idsAndPositionsWorms(idsAndPositionsWorms), idCurrenPlayer(VALUE_INITIAL), gameParameters(parameters) {
}

void Players::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players.emplace(idPlayer, Player(playerName, idPlayer, gameParameters));
}

void Players::assignWormsToPlayers() {
    size_t numberWorms = idsAndPositionsWorms.size();
    size_t numberPlayers = players.size();
    size_t iterations = numberWorms/numberPlayers;
    // obtengo los ids de los worms y de los players y los randomizamos en 2 vectores.
    std::vector<int> idWormsOrig, idPlayersOrig, idWormsCopy, idPlayersCopy;
    for (auto it = idsAndPositionsWorms.begin(); it != idsAndPositionsWorms.end(); it++) {
        idWormsOrig.push_back(it->first);
    }
    for (auto it = players.begin(); it != players.end(); it++) {
        idPlayersOrig.push_back(it->first);
    }
    std::random_shuffle(idWormsOrig.begin(), idWormsOrig.end());
    std::random_shuffle(idPlayersOrig.begin(), idPlayersOrig.end());
    size_t i = 0;
    idPlayersCopy = idPlayersOrig;
    idWormsCopy = idWormsOrig;
    while ( i < iterations ) {
        idPlayersCopy = idPlayersOrig;
        while ( !idWormsCopy.empty() && !idPlayersCopy.empty() ) {
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()]);
            idPlayersCopy.pop_back();
            idWormsCopy.pop_back();
        }
        i++;
    }
    if ( (numberWorms % numberPlayers) != 0 ) {
        idPlayersCopy = idPlayersOrig;
        while ( !idWormsCopy.empty() ) {
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()]);
            idWormsCopy.pop_back();
            idPlayersCopy.pop_back();
        }
        while ( !idPlayersCopy.empty() ) {
            players.at(idPlayersCopy.back()).assignBonusLife();
            idPlayersCopy.pop_back();
        }
    }
}

std::vector<WormDTO> Players::getWormsDTO() const {
    std::vector<WormDTO> wormsDTOCompl;
    for (auto it = players.begin();  it != players.end(); it++) {
        std::vector<WormDTO> vecWormsDTO =  (it->second.getWormsDTO());
        wormsDTOCompl.insert(wormsDTOCompl.end(), vecWormsDTO.begin(), vecWormsDTO.end() );
    }
    return wormsDTOCompl;
}

bool Players::onlyExistsOnePlayer() {
    size_t playerLoser = 0;
    for (auto& element : players) {
        if (element.second.lostAllWorms()) {
            playerLoser++;
        }
    }
    if ( this->players.size() == 1 && playerLoser == 0 ) {
        // soy un unico jugador-Test pero aun no perdi todo mis gusano quiero jugar solo.
        return false;
    } else if ( this->players.size() == 1 && playerLoser == 1 ) {
        // si era un unico jugador y perdi mi  worm entonces salgo.
        return true;
    }
    return (playerLoser == (this->players.size() -1) );
    // este ultima respt es para los juegos normalees  +2 de jugadores.
}

void Players::addToTheWorld(b2World *world) {
    for (auto& aPlayer : players) {
        aPlayer.second.addToTheWorld(world);
    }
}
//  Inicia el turno del jugador y nos escupe del nuevo id del jugador actual.
size_t Players::startAPlayerTurn() {
    if (idCurrenPlayer == VALUE_INITIAL) {
        playerIterator = players.begin();
        this->idCurrenPlayer = playerIterator->first;
        return idCurrenPlayer;
    }
    while ( playerIterator != players.end() ) {
        playerIterator++;
        if (playerIterator == players.end()) {
            playerIterator = players.begin();
        }
        if ( playerIterator != players.end() && !players.at(playerIterator->first).lostAllWorms() ) {
            break;
        }
    }
    this->idCurrenPlayer = playerIterator->first;
    return this->idCurrenPlayer;
}

void Players::update() {
    for (auto& aPlayer : players) {
        aPlayer.second.update();
        // actualizamos a todos los player pero muy a fonod los worms destruidos no seran actualizados
    }
}

PlayersDTO Players::getPlayersDTO() const {
    std::vector<PlayerDTO> vecPlayersDTO;
    for (auto& mapPlayers : players) {
        vecPlayersDTO.push_back(mapPlayers.second.getPlayerDTO(idCurrenPlayer));
    }
    return PlayersDTO(vecPlayersDTO);
}

std::vector<WeaponsDTO> Players::getVecWeaponsDTO() const {
    std::vector<WeaponsDTO> vecWeaponsDTO;
    for (auto& mapPlayers : players) {
        vecWeaponsDTO.push_back(mapPlayers.second.getWeaponsDTO());
    }
    return vecWeaponsDTO;
}

Worm * Players::getCurrentWorm() {
    return players.at(idCurrenPlayer).getCurrentWorm();
}

Player & Players::getCurrentPlayer() {
    return this->players.at(idCurrenPlayer);
}

bool Players::allWormsAreUnmoveAndNotExistsProjectiles() {
    for (auto& mapPlayers : players) {
        if (!mapPlayers.second.allWormsAreUnmoveAndNotExistsProjectiles()) {
            return false;
        }
    }
    return true;
}

std::vector<EndGameDTO> Players::getVecEndGameDTO() {
    std::vector<EndGameDTO> vecEndGameDTO;
    for (auto& mapPlayers : players) {
        vecEndGameDTO.push_back(mapPlayers.second.getEndGameDTO());
    }
    return vecEndGameDTO;
}

void Players::setLifeAllWorm(const float &aNewHP) {
    for (auto& aPlayer : players) {
        aPlayer.second.setLifeAllWorm(aNewHP);
    }
}

void Players::getMovingWorms(std::vector<std::pair<size_t, size_t>>& idPlayerAndWorm) {
    for (auto& aPlayer : players) {
        aPlayer.second.getMovingWorms(idPlayerAndWorm);
    }
}

void Players::assignTypeFocus(const TypeFocus &focus, const size_t &playerID, const size_t &wormID) {
    players.at(playerID).getWorm(wormID)->get()->assignTypeFocus(focus);
}

void Players::disableAllFocus() {
    for (auto& aPlayer : players) {
        aPlayer.second.disableAllFocus();
    }
}

