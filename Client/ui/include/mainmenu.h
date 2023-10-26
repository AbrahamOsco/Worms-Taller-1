#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "crearpartida.h"
#include "buscarpartida.h"
#include "socket.h"

class MainMenu : public QWidget {
private:
    Socket socket;
    CrearPartida crear;
    BuscarPartida buscar;
public:
    explicit MainMenu(QWidget *parent = 0,char* server=0,char* data = 0);
private:
    void crearPartida();
    void buscarPartida();
    void salir();
    void connectEvents();
};
#endif 
