#include <QApplication>
#include "login.h"
#include "mainmenu.h"

int main(int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    Login login;
    login.show();
    // Arranca el loop de la UI
    int i = app.exec();
    MainMenu mainmenu;
    mainmenu.show();
    return app.exec();
}
