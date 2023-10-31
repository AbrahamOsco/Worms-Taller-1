#include <qt5/QtWidgets/QApplication>
#include "protocol/ClientProtocol.h"
#include "game/Game.h"
#include "login.h"

int main (int argc, char *argv[]) {
    // Clase que contiene el loop principal
    QApplication app(argc, argv);
    // Instancio el greeter
    Login login;
    login.show();
    // Arranca el loop de la UI
    app.exec();

    //Game game(skt);
    //game.loadMap();
    //game.run();
    return 0;
}