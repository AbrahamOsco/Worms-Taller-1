#ifndef BUSCARPARTIDA_H
#define BUSCARPARTIDA_H

#include <QWidget>

class BuscarPartida : public QWidget {
public:
    explicit BuscarPartida(QWidget *parent = 0);
private:
    void unirse();
    void mostrar();
    void actualizar();
    void salir();
    void connectEvents();
};
#endif 
