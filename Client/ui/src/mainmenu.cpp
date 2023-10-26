#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent,char* server,char* port) : 
                                    QWidget(parent),
                                    socket(server,port) {
    Ui::MainMenu mainMenu;
    mainMenu.setupUi(this);
    connectEvents();
}

void MainMenu::crearPartida() {
    crear.show();
}
void MainMenu::salir(){
    this->close();
}
void MainMenu::buscarPartida(){
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
