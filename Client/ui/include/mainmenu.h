#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "crearpartida.h"

class MainMenu : public QWidget {
private:
    CrearPartida crear;
public:
    explicit MainMenu(QWidget *parent = 0);
private:
    void crearPartida();
    void buscarPartida();
    void salir();
    void connectEvents();
};
#endif 
