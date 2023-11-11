#include "WormDTO.h"
WormDTO::WormDTO() : DTO(WORM) {
}


WormDTO::WormDTO(const size_t &positionX, const size_t &positionY, const size_t& idPlayer,  const size_t &hpWorm, const Direction &aDirection,
                 const TypeFocusWorm &aTypeFocus, const MoveWorm &aMoveWorm, const TypeWeapon& weaponCurrent) : DTO(WORM), positionX(positionX), positionY(positionY),
                 idPlayer(idPlayer), hpWorm(hpWorm), directionLook(aDirection), moveWorm(aMoveWorm), typeFocus(aTypeFocus), weaponCurrent(weaponCurrent) {
}



size_t WormDTO::getPositionX() const {
    return positionX;
}

size_t WormDTO::getPositionY() const {
    return positionY;
}

size_t WormDTO::getHpWorm() const {
    return hpWorm;
}

Direction WormDTO::getDirectionLook() const {
    return directionLook;
}

TypeFocusWorm WormDTO::getTypeFocus() const {
    return typeFocus;
}

MoveWorm WormDTO::getMoveWorm() const {
    return moveWorm;
}

TypeWeapon WormDTO::getWeaponCurrent() const {
    return weaponCurrent;
}

size_t WormDTO::getIdPlayer() const {
    return this->idPlayer;
}

void WormDTO::setPositionX(const size_t &positionX) {
    this->positionX = positionX;
}

void WormDTO::setPositionY(const size_t &positionY) {
    this->positionY = positionY;
}

void WormDTO::setHpWorm(const size_t &hpWorm) {
    this->hpWorm = hpWorm;
}

void WormDTO::setDirectionLook(const Direction &directionLook) {
    this->directionLook = directionLook;
}

void WormDTO::setTypeFocus(const TypeFocusWorm &typeFocus) {
    this->typeFocus = typeFocus;
}

void WormDTO::setMoveWorm(const MoveWorm &moveWorm) {
    this->moveWorm = moveWorm;
}

void WormDTO::setWeaponCurrent(const TypeWeapon &weaponCurrent) {
    this->weaponCurrent = weaponCurrent;
}

void WormDTO::setIdPlayer(size_t idPlayer) {
    this->idPlayer = idPlayer;
}


