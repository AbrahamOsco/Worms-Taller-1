#ifndef BUSCARPARTIDA_H
#define BUSCARPARTIDA_H

#include <QWidget>
#include "socket.h"
#include <string>

struct Partida{
    std::string nombre;
    std::string mapa;
    size_t jugadores;
    size_t capacidad;
};

class BuscarPartida : public QWidget {
private:
    Socket* skt;
    std::vector<Partida> partidas;
public:
    explicit BuscarPartida(QWidget *parent = 0,Socket* socket = 0);
    void buscar(std::string& nombre);
private:
    void unirse();
    void mostrar();
    void salir();
    void connectEvents();
};
#endif 
