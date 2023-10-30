#ifndef CREARPARTIDA_H
#define CREARPARTIDA_H

#include <QWidget>
#include "socket.h"
#include <string>
#include "lobby.h"

class CrearPartida : public QWidget {
private:
    Socket* socket;
    QWidget* my_parent;
    Lobby lobby;
public:
    explicit CrearPartida(QWidget *parent = 0,Socket* skt=0);
    void buscar(std::string& nombre);
private:
    void crear();
    void connectEvents();
    void salir();
};
#endif 
