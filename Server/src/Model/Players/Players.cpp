//
// Created by abraham on 31/10/23.
//

#include "Players.h"
#include "../../../GameParameters/GameParameters.h"
#include <algorithm>
#include <iostream>

Players::Players(const std::map<size_t, std::pair<float, float>> &idsAndPositionsWorms, const GameParameters& parameters)
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
    idWormsCopy = idWormsOrig;
    idPlayersCopy = idPlayersOrig;
    // tenemos las copias y las originales, (asignamos la copia a la original nuevamente cuando la copia esta vacia).
    size_t i = 0;
    while( i < iterations){
        while( not idWormsCopy.empty() and not idPlayersCopy.empty() ){
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()]);
            idPlayersCopy.pop_back();
            idWormsCopy.pop_back();
        }
        idWormsCopy = idWormsOrig;
        idPlayersCopy = idPlayersOrig;
        i++;
    }
    // si la division entre el numero de gusanos y los jugadores no es exacta entonces falta gusanos para repartir.
    if ( (numberWorms % numberPlayers) != 0){
        idPlayersCopy = idPlayersOrig;
        idWormsCopy = idWormsOrig;
        while( not idWormsCopy.empty()){
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()] );
            idWormsCopy.pop_back();
            idPlayersCopy.back();
        }
        // Si ya no hay guasnos y hay jugadores que tienen menos gusanos (por q les falto repartir en esta vuelta) les damos la bonificacion de puntos.
        while ( not idPlayersCopy.empty()){
            players.at(idPlayersCopy.back()).assignBonusLife();
            idPlayersCopy.pop_back();
        }
    }
    startAPlayerTurn();
}

std::vector<WormDTO> Players::getWormsDTO() const{
    std::vector<WormDTO> wormsDTOCompl;
    for(auto it = players.begin();  it != players.end(); it++){
        std::vector<WormDTO> vecWormsDTO =  (it->second.getWormsDTO());
        wormsDTOCompl.insert(wormsDTOCompl.end(), vecWormsDTO.begin(), vecWormsDTO.end() );
    }
    return wormsDTOCompl;
}

void Players::addToTheWorld(b2World *world) {
    for(auto& aPlayer : players){
        aPlayer.second.addToTheWorld(world);
    }
}
//  Inicia el turno del jugador y nos escupe del nuevo id del jugador actual.
size_t Players::startAPlayerTurn() {
    if (idCurrenPlayer == VALUE_INITIAL){
        playerIterator = players.begin();
        this->idCurrenPlayer = playerIterator->first;
        return idCurrenPlayer;
    }
    playerIterator++;
    if ( playerIterator == players.end()){
        playerIterator = players.begin();
    }
    this->idCurrenPlayer = playerIterator->first;
    return this->idCurrenPlayer;
}

void Players::update() {
    for(auto& aPlayer : players){
        aPlayer.second.update();
    }
}

PlayersDTO Players::getPlayersDTO() const {
    std::vector<PlayerDTO> vecPlayersDTO;
    for(auto& mapPlayers : players){
        vecPlayersDTO.push_back(mapPlayers.second.getPlayerDTO(idCurrenPlayer));
    }
    return PlayersDTO(vecPlayersDTO);
}

std::vector<WeaponsDTO> Players::getVecWeaponsDTO() const {
    std::vector<WeaponsDTO> vecWeaponsDTO;
    for(auto& mapPlayers: players){
        vecWeaponsDTO.push_back(mapPlayers.second.getWeaponsDTO());
    }
    return vecWeaponsDTO;
}

Worm * Players::getCurrentWorm() {
    return players.at(idCurrenPlayer).getCurrentWorm();
}

Player & Players::getCurrentPlayer(){
    return this->players.at(idCurrenPlayer);
}

