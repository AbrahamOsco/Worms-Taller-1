#include "crearpartida.h"
#include "ui_crearpartida.h"
#include "socket.h"
#include <iostream>
#include <vector>

CrearPartida::CrearPartida(QWidget *parent,Socket* skt) : QWidget(parent) {
    socket = skt;
    Ui::CrearPartida crear;
    crear.setupUi(this);
    connectEvents();
}

void CrearPartida::crear() {
    this->hide();
}
void CrearPartida::buscar(){
    std::cout << socket << std::endl;
    uint8_t code = 0;
    uint8_t quantity = 0;
    bool closed = false;
    socket->sendall(&code,1,&closed);
    socket->recvall(&code,1,&closed);
    socket->recvall(&quantity,1,&closed);
    uint8_t lenght = 0;
    std::vector<char> map;
    QComboBox* maplist = findChild<QComboBox*>("listaMapas");
    maplist->clear();
    for(uint i = 0;i<quantity;i++){
        socket->recvall(&lenght,1,&closed);
        map.resize(lenght+1,0);
        socket->recvall(map.data(),lenght,&closed);
        std::cout << "si\n";
        std::string mapname(map.data());
        std::cout << "si\n";
        QString qmap = QString::fromStdString(mapname);
        std::cout << "si\n";
        maplist->addItem(qmap);
        std::cout << "si\n";
    }
}
void CrearPartida::connectEvents() {
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &CrearPartida::crear);
    QPushButton* buttonBuscar = findChild<QPushButton*>("buttonBuscar");
    QObject::connect(buttonBuscar, &QPushButton::clicked,
                     this, &CrearPartida::buscar);
}
