#ifndef CREARPARTIDA_H  // NOLINT
#define CREARPARTIDA_H

#include <QWidget>
#include <string>
#include <map>
#include <vector>
#include "../../../Common/Socket/Socket.h"
#include "./lobby.h"

class CrearPartida : public QWidget {
 private:
    Socket* socket;
    QWidget* my_parent;
    Lobby lobby;
    std::vector<std::string> namesScenarios;
    std::map<std::string, size_t> mapStageMaxWorm;
 public:
    explicit CrearPartida(QWidget *parent = 0, Socket* skt = 0);
    void buscar(const std::vector<std::string> &nameScenarios, std::map<std::string, size_t>& mapStageMaxWorm);  // NOLINT
 private:
    void crear();
    void connectEvents();
    void salir();
    void changeMax();
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // NOLINT
