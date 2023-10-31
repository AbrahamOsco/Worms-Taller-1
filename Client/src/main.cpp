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

    /*const char* ip = "127.0.0.1";
    const char* port = "8080";
    Socket skt(ip, port);
    Game game(skt);
    game.loadMap();
    game.run();*/
    return 0;
}