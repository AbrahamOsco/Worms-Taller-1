#include "buscarpartida.h"
#include "ui_buscarpartida.h"

BuscarPartida::BuscarPartida(QWidget *parent) : QWidget(parent) {
    Ui::BuscarPartida buscar;
    buscar.setupUi(this);
    connectEvents();
}

void BuscarPartida::unirse() {
}
void BuscarPartida::mostrar() {
}
void BuscarPartida::actualizar() {
}
void BuscarPartida::salir() {
    this->hide();
}
void BuscarPartida::connectEvents() {
    QPushButton* buttonUnirse = findChild<QPushButton*>("buttonUnirse");
    QObject::connect(buttonUnirse, &QPushButton::clicked,
                     this, &BuscarPartida::unirse);
    QPushButton* buttonMostrar = findChild<QPushButton*>("buttonMostrar");
    QObject::connect(buttonMostrar, &QPushButton::clicked,
                     this, &BuscarPartida::mostrar);
    QPushButton* buttonActualizar = findChild<QPushButton*>("buttonActualizar");
    QObject::connect(buttonActualizar, &QPushButton::clicked,
                     this, &BuscarPartida::actualizar);
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &BuscarPartida::salir);
}
