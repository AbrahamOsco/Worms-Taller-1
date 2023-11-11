#ifndef CREARPARTIDA_H
#define CREARPARTIDA_H

#include <QWidget>
#include "socket.h"
#include <string>
#include "lobby.h"
#include <map>

class CrearPartida : public QWidget {
private:
    Socket* socket;
    QWidget* my_parent;
    Lobby lobby;
    std::vector<std::string> namesScenarios;
    std::map<std::string, size_t> mapStageMaxWorm;
public:
    explicit CrearPartida(QWidget *parent = 0,Socket* skt=0);
    void buscar(const std::vector<std::string> &nameScenarios,std::map<std::string, size_t>& mapStageMaxWorm);
private:
    void crear();
    void connectEvents();
    void salir();
    void changeMax();
    void resizeEvent(QResizeEvent* event) override;
};
#endif
