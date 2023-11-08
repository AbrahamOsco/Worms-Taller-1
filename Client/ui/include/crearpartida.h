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
    std::vector<std::string> namesScenarios;
public:
    explicit CrearPartida(QWidget *parent = 0,Socket* skt=0);
    void buscar(const std::vector<std::string> &nameScenarios);
private:
    void crear();
    void connectEvents();
    void salir();
    void resizeEvent(QResizeEvent* event) override;
};
#endif 
