#include "crearpartida.h"
#include "ui_crearpartida.h"

CrearPartida::CrearPartida(QWidget *parent) : QWidget(parent) {
    Ui::CrearPartida crear;
    crear.setupUi(this);
    connectEvents();
    crear.listaMapas->addItem("Mapa 1");
    crear.listaMapas->addItem("Mapa 2");
}

void CrearPartida::crear() {
    this->close();
}
void CrearPartida::connectEvents() {
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &CrearPartida::crear);
}
