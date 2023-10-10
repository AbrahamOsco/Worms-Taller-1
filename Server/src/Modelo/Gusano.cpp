//
// Created by abraham on 07/10/23.
//

#include "Gusano.h"

Gusano::Gusano(const Posicion &unaPos, const float &unaVelocidad, const float &unaAltura, const float &unHp) :  posActual(unaPos),
        velocidad(unaVelocidad), alturaSalto(unaAltura), hp(unHp) {

}

void Gusano::moverse(const Direccion &unaDireccion) {
    if (unaDireccion == Direccion::IZQUIERDA){
        float nuevaCoordX = posActual.getCoordX()-1;
        posActual = Posicion(nuevaCoordX, posActual.getCoordY());
    } else if (unaDireccion == Direccion::DERECHA){
        float nuevaCoordX = posActual.getCoordX()+1;
        posActual = Posicion(nuevaCoordX, posActual.getCoordY());
    }

}



