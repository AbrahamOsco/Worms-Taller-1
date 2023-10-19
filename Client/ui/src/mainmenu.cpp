#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    Ui::MainMenu mainMenu;
    mainMenu.setupUi(this);
    connectEvents();
}

void MainMenu::exit() {
    this->close();
}

void MainMenu::connectEvents() {
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonSalir");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &MainMenu::exit);
}
