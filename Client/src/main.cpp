#include <qt5/QtWidgets/QApplication>
#include "protocol/ClientProtocol.h"
#include "game/Game.h"
#include "login.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Login login;
    login.show();
    app.exec();
    return 0;
}
