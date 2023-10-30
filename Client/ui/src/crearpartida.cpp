#include "crearpartida.h"
#include "ui_crearpartida.h"
#include "socket.h"
#include <iostream>
#include <vector>
#include <string>

CrearPartida::CrearPartida(QWidget *parent,Socket* skt) : 
                                    QWidget(parent){
    socket = skt;
    my_parent = parent;
    Ui::CrearPartida crear;
    crear.setupUi(this);
    connectEvents();
}

void CrearPartida::crear() {
    QLineEdit* inputName = findChild<QLineEdit*>("inputNombre");
    QComboBox* mapList = findChild<QComboBox*>("listaMapas");
    QComboBox* numberList = findChild<QComboBox*>("listaCantidad");
    QString qname = inputName->text();
    QString qmap = mapList->currentText();
    QString qnumber = mapList->currentText();
    std::string name = qname.toStdString();
    std::string map = qmap.toStdString();
    std::string snumber = qnumber.toStdString();
    size_t number = (size_t) std::stoi(snumber);
    //Envia nombre, mapa, numero
    //recibe respuesta
    //si es exitosa pasa al lobby
    //sino muestra que no se pudo crear
}
void CrearPartida::buscar(std::string& nombre){
    std::vector<std::string> map;
    //envia nombre y pedido de mapas
    //recibe mapas
    QComboBox* maplist = findChild<QComboBox*>("listaMapas");
    maplist->clear();
    for(uint i = 0;i<map.size();i++){
        QString qmap = QString::fromStdString(map[i]);
        maplist->addItem(qmap);
    }
}
void CrearPartida::salir(){
    this->close();
}
void CrearPartida::connectEvents() {
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &CrearPartida::crear);
    QPushButton* buttonVolver = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonVolver, &QPushButton::clicked,
                     this, &CrearPartida::salir);
}
