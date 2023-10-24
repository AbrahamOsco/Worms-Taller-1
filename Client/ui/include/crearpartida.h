#ifndef CREARPARTIDA_H
#define CREARPARTIDA_H

#include <QWidget>

class CrearPartida : public QWidget {
public:
    explicit CrearPartida(QWidget *parent = 0);
private:
    void crear();
    void connectEvents();
};
#endif 
