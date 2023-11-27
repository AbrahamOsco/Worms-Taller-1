#include "../include/mainmenu.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QPalette>
#include <map>
#include "ui_mainmenu.h"  // NOLINT
#include "../../src/protocol/ClientProtocol.h"

MainMenu::MainMenu(QWidget *parent, char* server, char* port, char* name) :
        QWidget(parent),
        socket(server, port),
        playerName(name),
        create(nullptr, &socket),
        search(nullptr, &socket) {
    Ui::MainMenu mainMenu;
    mainMenu.setupUi(this);
    connectEvents();
}

void MainMenu::createGame() {
    ClientProtocol clientProtocol(socket);
    InitialStateDTO initialState(SCENARIO_LIST_REQUEST, playerName);
    clientProtocol.sendInitialStateDTO(initialState);
    ResolverInitialDTO resolvIniCreate = clientProtocol.recvResolverInitialDTO();
    std::vector<size_t> vecMaxNumberWomrs = resolvIniCreate.getVecMaxNumbersWorms();
    std::map<std::string, size_t> mapStageMaxWorm;
    for (size_t i = 0 ; i < resolvIniCreate.getVecMaxNumbersWorms().size(); i++) {
        mapStageMaxWorm[ resolvIniCreate.getScenariosNames()[i] ] = resolvIniCreate.getVecMaxNumbersWorms()[i];
    }
    // guardar ese mapa como atributo y usarlo @GIRARDI
    create.search(resolvIniCreate.getScenariosNames(), mapStageMaxWorm);
    this->hide();
    create.show();
}

void MainMenu::exit() {
    this->close();
}

void MainMenu::searchGame() {
    ClientProtocol clientProtocol(socket);
    InitialStateDTO initialState(ROOM_LIST_REQUEST, playerName);
    clientProtocol.sendInitialStateDTO(initialState);
    ResolverInitialDTO resolvIniJoin = clientProtocol.recvResolverInitialDTO();
    search.search(resolvIniJoin.getGameRooms());
    this->hide();
    search.show();
}
void MainMenu::resizeEvent(QResizeEvent* event) {
    QPixmap pixmap("../Client/ui/resources/login.png");
    pixmap = pixmap.scaled(event->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
}
void MainMenu::connectEvents() {
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &MainMenu::exit);
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &MainMenu::createGame);
    QPushButton* buttonBuscar = findChild<QPushButton*>("buttonBuscar");
    QObject::connect(buttonBuscar, &QPushButton::clicked,
                     this, &MainMenu::searchGame);
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setWindowTitle("Worms-Main Menu");
}
