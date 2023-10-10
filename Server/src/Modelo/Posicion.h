//
// Created by abraham on 07/10/23.
//

#ifndef WORMS_TALLER_1_POSICION_H
#define WORMS_TALLER_1_POSICION_H


class Posicion {
private:
    float coordX;
    float coordY;

public:
    Posicion(const float& unaCoordX, const float& unaCoordY);

    float getCoordX() const;

    float getCoordY() const;

};


#endif //WORMS_TALLER_1_POSICION_H
