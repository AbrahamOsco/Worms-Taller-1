#include "lobby.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_lobby.h"
#include "socket.h"
#include <QTime>
#include "../../../Common/Queue/Queue.h"
#include "thread.h"
#include "waiter.h"
#include "../../src/game/Game.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include <QMovie>

Lobby::Lobby(QWidget *parent,Socket* socket) : QWidget(parent),
                                                timer(this),
                                                my_queue(200),
                                                skt(socket),
                                                waiter(skt,&my_queue){
    Ui::Lobby lobby;
    lobby.setupUi(this);
    timer.start(500);
    connectEvents();
}
void Lobby::empezar(){
    this->hide();
    Game game(*skt);
    game.loadMap();
    game.run();
    this->close();
}
void Lobby::update(){
    ResolverInitialDTO val;
    bool result = my_queue.try_pop(val);
    if (result){
        if (val.getOperationType() == START_GAME){
            waiter.join();
            this->empezar();
        }
    }
}
void Lobby::start(){
    waiter.start();
    timer.start(100);
}
void Lobby::connectEvents() {
    QObject::connect(&timer,&QTimer::timeout,this,&Lobby::update);
}