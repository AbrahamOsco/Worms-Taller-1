#include "../include/searchgame.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <string>
#include <iostream>
#include "ui_searchgame.h"  // NOLINT
#include "../include/lobby.h"
#include "../../src/protocol/ClientProtocol.h"


SearchGame::SearchGame(QWidget *parent, Socket* socket) :  QWidget(parent),
                                                                lobby(nullptr, socket) {
    skt = socket;
    Ui::SearchGame search;
    search.setupUi(this);
    connectEvents();
}

void SearchGame::join() {
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    QString qGameName = gameList->currentText();
    ClientProtocol clientProtocol(*skt);
    std::cout << "game a unrise: " << qGameName.toStdString();
    ResponseInitialStateDTO responseJoinGame(FINAL_JOIN_GAME, qGameName.toStdString());
    clientProtocol.sendResponseInitialStateDTO(responseJoinGame);
    std::cout << "Se envia con exito el ResponseInitialStateDTO \n";
    ResolverInitialDTO answerServer = clientProtocol.recvResolverInitialDTO();
    if (answerServer.getStatusAnswer() == SUCCESS_STATUS) {
        std::cout << "Se recibio con exito el SUCCESS_STATUS \n";
        this->hide();
        lobby.start();
        lobby.show();
    } else if (answerServer.getStatusAnswer() == ERROR_STATUS) {
        std::cout << "Se recibio un ERROR  el ERROR_STATUS \n";
        gameRooms.clear();
        this-> gameRooms = answerServer.getGameRooms();
        QLabel* labelResultado = findChild<QLabel*>("labelResult");
        QString update = QString("No se pudo unir a la partida, vuelva a intentar");
        labelResultado->setText(update);
    }
}
void SearchGame::showInfo() {
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
void SearchGame::exit() {
    this->close();
}

void SearchGame::search(const std::vector<RoomDTO> &gameRooms) {
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    gameList->clear();
    this->gameRooms = gameRooms;

    for (size_t i = 0; i < gameRooms.size(); i++) {
        QString qGameName = QString::fromStdString(gameRooms[i].getGameName());
        gameList->addItem(qGameName);
    }
}
void SearchGame::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap("../Client/ui/resources/create-search.jpg");
    pixmap = pixmap.scaled(event->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}
void SearchGame::connectEvents() {
    QPushButton* buttonUnirse = findChild<QPushButton*>("buttonUnirse");
    QObject::connect(buttonUnirse, &QPushButton::clicked,
                     this, &SearchGame::join);
    QComboBox* gameList = findChild<QComboBox*>("listaPartidas");
    QObject::connect(gameList, &QComboBox::currentTextChanged,
                     this, &SearchGame::showInfo);
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &SearchGame::exit);
    this->setWindowTitle("Worms-Buscar Partida");
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}
