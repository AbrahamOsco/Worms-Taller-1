#include "protocol/ClientProtocol.h"
#include "game/Game.h"

int main () {
    const char* ip = "127.0.0.1";
    const char* port = "8080";

    Socket skt(ip, port);
    /*
     * Aca va el looby de QT
     */
    Game game(skt);
    game.loadMap();
    game.run();
    return 0;
}