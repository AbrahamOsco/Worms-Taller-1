#ifndef MAINMENU_H  // NOLINT
#define MAINMENU_H

#include <QWidget>
#include <QPixmap>
#include <string>
#include "./crearpartida.h"
#include "./buscarpartida.h"
#include "./socket.h"


class MainMenu : public QWidget {
 private:
    Socket socket;
    std::string playerName;
    CrearPartida crear;
    BuscarPartida buscar;
    QPixmap pixmap;

 public:
    explicit MainMenu(QWidget *parent = 0, char* server = 0, char* data = 0, char* name = 0);
 private:
    void crearPartida();
    void buscarPartida();
    void salir();
    void connectEvents();
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // NOLINT
