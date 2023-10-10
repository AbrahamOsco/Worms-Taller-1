//
// Created by abraham on 07/10/23.
//

#ifndef WORMS_TALLER_1_GUSANO_H
#define WORMS_TALLER_1_GUSANO_H


#include "Posicion.h"
enum Direccion { IZQUIERDA = 0, DERECHA = 1 };

class Gusano {
private:
    float velocidad;
    float alturaSalto;
    float hp;
    Posicion posActual;


public:
    Gusano(const Posicion& unaPos, const float& unaVelocidad, const float& unaAltura, const float& unHp);
    void moverse(const Direccion& unaDireccion);

};


#endif //WORMS_TALLER_1_GUSANO_H
