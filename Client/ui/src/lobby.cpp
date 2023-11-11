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
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>

Lobby::Lobby(QWidget *parent,Socket* socket) : QWidget(parent),
                                                timer(this),
                                                my_queue(200),
                                                skt(socket),
                                                waiter(skt,&my_queue),
                                                gif(QMovie("../Client/ui/resources/waiting.gif")){
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
    QLabel* labelGif = findChild<QLabel*>("labelGif");
    labelGif->setMovie(&gif);
    gif.start();
    timer.start(500);
}
void Lobby::play(){

}
void Lobby::stop(){

}
void Lobby::connectEvents() {
    QObject::connect(&timer,&QTimer::timeout,this,&Lobby::update);
    this->setWindowTitle("Worms-Lobby");
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}
