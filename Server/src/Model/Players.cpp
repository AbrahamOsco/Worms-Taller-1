//
// Created by abraham on 31/10/23.
//

#include "Players.h"
#include <algorithm>

Players::Players(const std::map<size_t, std::pair<float, float>> &idsAndPositionsWorms) : idsAndPositionsWorms(idsAndPositionsWorms), idCurrenPlayer(VALUE_INITIAL) {

}

void Players::addPlayer(const std::string &playerName, const size_t &idPlayer) {
    players[idPlayer] = Player(playerName, idPlayer);
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
            players[ idPlayersCopy.back() ].assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()]);
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
            players[idPlayersCopy.back()].assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()] );
            idWormsCopy.pop_back();
            idPlayersCopy.back();
        }
        // Si ya no hay guasnos y hay jugadores que tienen menos gusanos (por q les falto repartir en esta vuelta) les damos la bonificacion de puntos.
        while ( not idPlayersCopy.empty()){
            players[idPlayersCopy.back()].assignBonusLife();
            idPlayersCopy.pop_back();
        }
    }

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

size_t Players::getCurrentPlayerId() {
    if (idCurrenPlayer == VALUE_INITIAL){
        playerIterator = players.begin();
        this->idCurrenPlayer = playerIterator->first;
        return idCurrenPlayer;
    }
    idCurrenPlayer++;
    if ( playerIterator == players.end()){
        playerIterator = players.begin();
    }
    this->idCurrenPlayer = playerIterator->first;
    return this->idCurrenPlayer;
}

std::pair<size_t, size_t> Players::getIdPlayerWormCurrent(){
    size_t idPlayerCurrent = this->getCurrentPlayerId();
    return std::make_pair(idPlayerCurrent, players[idPlayerCurrent].getCurrentWormId());
}

void Players::leftWorm() {
    players[idCurrenPlayer].leftWorm();
}

void Players::rightWorm() {
    players[idCurrenPlayer].rightWorm();
}

void Players::jumpBackWorm() {
    players[idCurrenPlayer].jumpBackWorm();
}

void Players::jumpForwardWorm() {
    players[idCurrenPlayer].jumpForwardWorm();
}
