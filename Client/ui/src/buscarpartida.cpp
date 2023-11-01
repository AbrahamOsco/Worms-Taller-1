#include "buscarpartida.h"
#include "ui_buscarpartida.h"
#include <string>
#include <iostream>
#include "lobby.h"
#include "../../src/protocol/ClientProtocol.h"


BuscarPartida::BuscarPartida(QWidget *parent,Socket* socket) :  QWidget(parent),
                                                                lobby(nullptr,socket){
    skt = socket;
    Ui::BuscarPartida buscar;
    buscar.setupUi(this);
    connectEvents();
}

void BuscarPartida::unirse() {
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    QString qGameName = gameList->currentText();
    ClientProtocol clientProtocol(*skt);
    std::cout << "game a unrise: " << qGameName.toStdString();
    ResponseInitialStateDTO responseJoinGame(FINAL_JOIN_GAME, qGameName.toStdString());
    clientProtocol.sendResponseInitialStateDTO(responseJoinGame);
    std::cout << "Se envia con exito el ResponseInitialStateDTO \n";

    ResolverInitialDTO answerServer = clientProtocol.recvResolverInitialDTO();
    if(answerServer.getStatusAnswer() == SUCCESS_STATUS ){
        std::cout << "Se recibio con exito el SUCCESS_STATUS \n";
        this->hide();
        lobby.start();
        lobby.show();
    } else if ( answerServer.getStatusAnswer() == ERROR_STATUS){
        std::cout << "Se recibio un ERROR  el ERROR_STATUS \n";
        // limpiamos los rooms q tenemos (Desactualizado) y ademas del error obtenemos los nuevos rooms disponibles.
        gameRooms.clear();
        this-> gameRooms = answerServer.getGameRooms();
        // volver a mostrar este stage con estos nuevos Rooms @Girardi.
    }

}
void BuscarPartida::mostrar() {
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    int i = gameList->currentIndex();
    QLabel* labelMap = findChild<QLabel*>("labelEscenario");
    QLabel* labelJugadores = findChild<QLabel*>("labelNum");
    QLabel* labelCap = findChild<QLabel*>("labelCapacidad");
    QString aux = QString::fromStdString(gameRooms[i].getScenarioName());
    QString update = QString("Scenario: %1").arg(aux);
    labelMap->setText(update);
    aux = QString::fromStdString(std::to_string(gameRooms[i].getPlayerCurrent()));
    update = QString("Jugadores Actuales : %1").arg(aux);
    labelJugadores->setText(update);
    aux = QString::fromStdString(std::to_string(gameRooms[i].getPlayerRequired()));
    update = QString("Jugadores Requeridos: %1").arg(aux);
    labelCap->setText(update);
}
void BuscarPartida::salir() {
    this->close();
}

void BuscarPartida::buscar(const std::vector<RoomDTO> &gameRooms){
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    gameList->clear();
    this->gameRooms = gameRooms;

    for(size_t i = 0; i<gameRooms.size(); i++){
        QString qGameName = QString::fromStdString(gameRooms[i].getGameName());
        gameList->addItem(qGameName);
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
