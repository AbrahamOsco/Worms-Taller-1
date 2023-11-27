#include "../include/creategame.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <iostream>
#include <vector>
#include <string>
#include "ui_creategame.h"  // NOLINT
#include "../../../Common/Socket/Socket.h"
#include "../include/lobby.h"
#include "../../../Common/DTO/ResponseInitialStateDTO.h"
#include "../../src/protocol/ClientProtocol.h"

#define EXIT_S

CreateGame::CreateGame(QWidget *parent, Socket* skt):
                                    QWidget(parent),
                                    lobby(nullptr, skt) {
    socket = skt;
    my_parent = parent;
    Ui::CreateGame create;
    create.setupUi(this);
    connectEvents();
}
void CreateGame::create() {
    QLineEdit* inputName = findChild<QLineEdit*>("inputNombre");
    QComboBox* mapList = findChild<QComboBox*>("listaMapas");
    QComboBox* numberList = findChild<QComboBox*>("listaCantidad");
    QString qGameName = inputName->text();
    QString qScenarioName = mapList->currentText();
    QString qPlayerRequired = numberList->currentText();
    size_t playersRequired = std::stoi(qPlayerRequired.toStdString());
    ResponseInitialStateDTO responIniCreateGame(FINAL_CREATE_GAME, qGameName.toStdString(),
                                                qScenarioName.toStdString(), playersRequired);
    ClientProtocol clientProtocol(*socket);
    bool closed = false;
    clientProtocol.sendResponseInitialStateDTO(responIniCreateGame);
    ResolverInitialDTO answerServer = clientProtocol.recvResolverInitialDTO();
    if (answerServer.getStatusAnswer() == SUCCESS_STATUS) {
        lobby.start();
        this->hide();
        lobby.show();
    } else if (answerServer.getStatusAnswer() == ERROR_STATUS) {
        QLabel* labelResultado = findChild<QLabel*>("labelResultado");
        QString update = QString("No se pudo crear la partida, vuelva a intentar");
        labelResultado->setText(update);
    }
}

void CreateGame::search(const std::vector<std::string> &nameScenarios,
                            std::map<std::string, size_t>& mapStageMaxWorm) {
    this->mapStageMaxWorm = mapStageMaxWorm;
    this->namesScenarios = nameScenarios;
    QComboBox* maplist = findChild<QComboBox*>("listaMapas");
    maplist->clear();
    for (uint i = 0; i < nameScenarios.size(); i++) {
        QString qmap = QString::fromStdString(nameScenarios[i]);
        maplist->addItem(qmap);
    }
}
void CreateGame::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap("../Client/ui/resources/create-search.jpg");
    pixmap = pixmap.scaled(event->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}
void CreateGame::exit() {
    this->close();
}
void CreateGame::changeMax() {
    QComboBox* mapList = findChild<QComboBox*>("listaMapas");
    QComboBox* maxList = findChild<QComboBox*>("listaCantidad");
    maxList->clear();
    QString qmap = mapList->currentText();
    std::string map = qmap.toStdString();
    size_t maxPlayer = mapStageMaxWorm[map];
    for (size_t i = 1; i <= maxPlayer; i++) {
        std::string number = std::to_string(i);
        QString qnumber = QString::fromStdString(number);
        maxList->addItem(qnumber);
    }
}
void CreateGame::connectEvents() {
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &CreateGame::create);
    QPushButton* buttonVolver = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonVolver, &QPushButton::clicked,
                     this, &CreateGame::exit);
    QComboBox* mapList = findChild<QComboBox*>("listaMapas");
    QObject::connect(mapList, &QComboBox::currentTextChanged,
                     this, &CreateGame::changeMax);
    this->setWindowTitle("Worms-Crear Partida");
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}
