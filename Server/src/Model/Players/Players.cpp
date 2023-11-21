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
    // tenemos las copias y las originales, (asignamos la copia a la original nuevamente cuando la copia esta vacia).
    size_t i = 0;
    // tenemos 2 gusano  y 1 jugador. -> 1 jugador con los 2 gusanos.
    // tenemos 4 gusanos y 2 jugadores -> J:0 -> id = 1. J:1 -> id = 2 ,  J:0 -> id = 0  J:1 ->  id = 3.
    idPlayersCopy = idPlayersOrig;
    idWormsCopy = idWormsOrig;
    while( i < iterations){
        idPlayersCopy = idPlayersOrig;
        while( not idWormsCopy.empty() and not idPlayersCopy.empty() ){
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()]);
            idPlayersCopy.pop_back();
            idWormsCopy.pop_back();
        }
        i++;
    }
    // si la division entre el numero de gusanos y los jugadores no es exacta entonces falta gusanos para repartir que quedaron  OJO.
    if ( (numberWorms % numberPlayers) != 0){
        idPlayersCopy = idPlayersOrig;
        while( not idWormsCopy.empty()){
            players.at(idPlayersCopy.back()).assignWorm(idWormsCopy.back(), idsAndPositionsWorms[idWormsCopy.back()] );
            idWormsCopy.pop_back();
            idPlayersCopy.pop_back();
        }
        // Si ya no hay gusanos y hay jugadores que tienen menos gusanos (por q les falto repartir en esta vuelta) les damos la bonificacion de puntos.
        while ( not idPlayersCopy.empty()){
            players.at(idPlayersCopy.back()).assignBonusLife();
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
bool Players::onlyExistsOnePlayer(){
    size_t playerLoser = 0;
    for(auto& element: players){
        if(element.second.lostAllWorms()){
            playerLoser++;
        }
    }
    if(this->players.size() == 1 and playerLoser == 0 ){ // soy un unico jugador-Test pero aun no perdi todo mis gusano quiero jugar solo.
        return false;
    } else if (this->players.size() == 1 and playerLoser == 1 ){ // si era un unico jugador y perdi mi  worm entonces salgo.
        return true;
    }
    return (playerLoser == (this->players.size() -1) ); // este ultima respt es para los juegos normalees  +2 de jugadores.
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
    while( playerIterator != players.end() ){
        playerIterator++;
        if(playerIterator == players.end()){
            playerIterator = players.begin();
        }
        if( not players.at(playerIterator->first).lostAllWorms() ){
            break;
        }
    }
    this->idCurrenPlayer = playerIterator->first;
    return this->idCurrenPlayer;
}

void Players::update() {
    for(auto& aPlayer : players) {
        aPlayer.second.update();        //actualizamos a todos los player pero muy a fonod los worms destruidos no seran actualizados
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

bool Players::allWormsAreUnmoveAndNotExistsProjectiles() {
    for(auto& mapPlayers : players){
        if(not mapPlayers.second.allWormsAreUnmoveAndNotExistsProjectiles()){
            return false;
        }
    }
    return true;
}

std::vector<EndGameDTO> Players::getVecEndGameDTO() {
    std::vector<EndGameDTO> vecEndGameDTO;
    for(auto& mapPlayers: players){
        vecEndGameDTO.push_back(mapPlayers.second.getEndGameDTO()) ;
    }
    return vecEndGameDTO;
}


