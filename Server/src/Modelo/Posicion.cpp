//
// Created by abraham on 07/10/23.
//

#include "Posicion.h"

Posicion::Posicion(const float& unaCoordX, const float& unaCoordY) : coordX(unaCoordX), coordY(unaCoordY){

}

float Posicion::getCoordX() const {
    return coordX;
}

float Posicion::getCoordY() const {
    return coordY;
}
