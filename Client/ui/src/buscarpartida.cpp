#include "buscarpartida.h"
#include "ui_buscarpartida.h"
#include <string>
#include <iostream>

BuscarPartida::BuscarPartida(QWidget *parent,Socket* socket) : QWidget(parent) {
    skt = socket;
    Ui::BuscarPartida buscar;
    buscar.setupUi(this);
    connectEvents();
}

void BuscarPartida::unirse() {
    //lanza el lobby
}
void BuscarPartida::mostrar() {
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    int i = gameList->currentIndex();
    QLabel* labelMap = findChild<QLabel*>("labelEscenario");
    QLabel* labelJugadores = findChild<QLabel*>("labelNum");
    QLabel* labelCap = findChild<QLabel*>("labelCapacidad");
    QString aux = QString::fromStdString(partidas[i].mapa);
    QString update = QString("Mapa: %1").arg(aux);
    labelMap->setText(update);
    aux = QString::fromStdString(std::to_string(partidas[i].jugadores));
    update = QString("Jugadores: %1").arg(aux);
    labelJugadores->setText(update);
    aux = QString::fromStdString(std::to_string(partidas[i].capacidad));
    update = QString("Capacidad: %1").arg(aux);
    labelCap->setText(update);
}
void BuscarPartida::salir() {
    this->close();
}
void BuscarPartida::buscar(std::string& nombre){
    //hace request de todas las partidas
    //recibo el vector, lo guardo en my vector
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    gameList->clear();
    Partida partida;
    partida.nombre = "panchito";
    partida.mapa = "mapa pequeño";
    partida.jugadores = 1;
    partida.capacidad = 4;
    partidas.push_back(partida);
    partida.nombre = "paty";
    partida.mapa = "mapa grande";
    partida.jugadores = 2;
    partida.capacidad = 4;
    partidas.push_back(partida);
    for (int i = 0;i<partidas.size();i++){
        QString qgame = QString::fromStdString(partidas[i].nombre);
        gameList->addItem(qgame);
    }
}
void BuscarPartida::connectEvents() {
    QPushButton* buttonUnirse = findChild<QPushButton*>("buttonUnirse");
    QObject::connect(buttonUnirse, &QPushButton::clicked,
                     this, &BuscarPartida::unirse);
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    QObject::connect(gameList, &QComboBox::currentTextChanged,
                     this, &BuscarPartida::mostrar);
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &BuscarPartida::salir);
}
