#include "crearpartida.h"
#include "ui_crearpartida.h"
#include "socket.h"
#include <iostream>
#include <vector>
#include <string>
#include "lobby.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../src/protocol/ClientProtocol.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#define EXIT_S

CrearPartida::CrearPartida(QWidget *parent,Socket* skt) : 
                                    QWidget(parent),
                                    lobby(nullptr,skt){
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
    ClientProtocol clientProtocol(*socket);  // ver si explota es por esto
    bool closed = false;
    clientProtocol.sendResponseInitialStateDTO(responIniCreateGame);
    ResolverInitialDTO answerServer = clientProtocol.recvResolverInitialDTO();
    if(answerServer.getStatusAnswer() == SUCCESS_STATUS ){
        lobby.start();
        this->hide();
        lobby.show();
    } else if ( answerServer.getStatusAnswer() == ERROR_STATUS ){
        QLabel* labelResultado = findChild<QLabel*>("labelResultado");
        QString update = QString("No se pudo crear la partida, vuelva a intentar");
        labelResultado->setText(update);
    }
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
void CrearPartida::resizeEvent(QResizeEvent* event){
    QPixmap pixmap("../Client/ui/resources/create-search.jpg");
    pixmap = pixmap.scaled(event->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window,pixmap);
    this->setPalette(palette);
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
    this->setWindowTitle("Worms-Crear Partida");
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y); 
}
