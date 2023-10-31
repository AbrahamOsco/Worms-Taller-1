#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "../../src/protocol/ClientProtocol.h"

MainMenu::MainMenu(QWidget *parent,char* server,char* port,char* name) :
        QWidget(parent),
        socket(server,port),
        playerName(name),
        crear(nullptr,&socket),
        buscar(nullptr,&socket) {
    Ui::MainMenu mainMenu;
    mainMenu.setupUi(this);
    connectEvents();
}

void MainMenu::crearPartida() {
    ClientProtocol clientProtocol(socket);
    InitialStateDTO initialState(SCENARIO_LIST_REQUEST, playerName);
    clientProtocol.sendInitialStateDTO(initialState);
    ResolverInitialDTO resolvIniCreate = clientProtocol.recvResolverInitialDTO();
    std::vector<std::string> nameScenarios;
    crear.buscar(nameScenarios);

    this->hide();
    crear.show();
}

void MainMenu::salir(){
    this->close();
}

void MainMenu::buscarPartida(){
    ClientProtocol clientProtocol(socket);
    InitialStateDTO initialState(ROOM_LIST_REQUEST, playerName);
    clientProtocol.sendInitialStateDTO(initialState);
    ResolverInitialDTO resolvIniJoin = clientProtocol.recvResolverInitialDTO();
    buscar.buscar(resolvIniJoin.getGameRooms());
    this->hide();
    buscar.show();
}

void MainMenu::connectEvents() {
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &MainMenu::salir);
    QPushButton* buttonCrear = findChild<QPushButton*>("buttonCrear");
    QObject::connect(buttonCrear, &QPushButton::clicked,
                     this, &MainMenu::crearPartida);
    QPushButton* buttonBuscar = findChild<QPushButton*>("buttonBuscar");
    QObject::connect(buttonBuscar, &QPushButton::clicked,
                     this, &MainMenu::buscarPartida);                           
}
