#ifndef CREARPARTIDA_H
#define CREARPARTIDA_H

#include <QWidget>
#include "socket.h"

class CrearPartida : public QWidget {
public:
    Socket* socket;
    explicit CrearPartida(QWidget *parent = 0,Socket* skt=0);
private:
    void crear();
    void buscar();
    void connectEvents();
};
#endif 
