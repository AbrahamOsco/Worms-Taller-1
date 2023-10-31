#include "crearpartida.h"
#include "ui_crearpartida.h"
#include "socket.h"
#include <iostream>
#include <vector>
#include <string>
#include "lobby.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../src/protocol/ClientProtocol.h"
#define EXIT_S

CrearPartida::CrearPartida(QWidget *parent,Socket* skt) : 
                                    QWidget(parent),
                                    lobby(nullptr,socket){
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
    QString qGameName = inputName->text();
    QString qScenarioName = mapList->currentText();
    QString qPlayerRequired = numberList->currentText();
    size_t playersRequired = std::stoi(qPlayerRequired.toStdString());
    ResponseInitialStateDTO responIniCreateGame(FINAL_CREATE_GAME, qGameName.toStdString(), qScenarioName.toStdString(), playersRequired);
    ClientProtocol clientProtocol(reinterpret_cast<Socket &>(socket));  // ver si explota es por esto
    clientProtocol.sendResponseInitialStateDTO(responIniCreateGame);
    ResolverInitialDTO answerServer = clientProtocol.recvResolverInitialDTO();
    if(answerServer.getStatusAnswer() == SUCCESS_STATUS ){
        this->hide();
        lobby.start();
        lobby.show();
    } else if ( answerServer.getStatusAnswer() == ERROR_STATUS ){
        // Mostrar que no se puddo crear y de alguna manera resetear todos los campos y volver a mostrar el stage CrearPartida
        // Como estan cacheado los scenariosName (es un atributo) no hay problema. @Girardi
    }
    this->hide();
    lobby.start();
    lobby.show();

}

void CrearPartida::buscar(const std::vector<std::string> &nameScenarios){
    this->namesScenarios = nameScenarios;
    QComboBox* maplist = findChild<QComboBox*>("listaMapas");
    maplist->clear();
    for(uint i = 0; i<nameScenarios.size(); i++){
        QString qmap = QString::fromStdString(nameScenarios[i]);
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
