#include "lobby.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_lobby.h"
#include "socket.h"
#include <QTime>
#include "../Common/Queue/Queue.h"
#include "thread.h"
#include "waiter.h"
#include "../../src/game/Game.h"

Lobby::Lobby(QWidget *parent,Socket* socket) : QWidget(parent),
                                                timer(this),
                                                my_queue(200),
                                                waiter(socket,&my_queue) {
    skt = socket;
    Ui::Lobby lobby;
    lobby.setupUi(this);
    timer.start(500);
    connectEvents();
}
void Lobby::enviar(){
    QListWidget* chat = findChild<QListWidget*>("chat");
    QLineEdit* inputChat = findChild<QLineEdit*>("inputChat");
    QString qchat = inputChat->text();
    chat->addItem(qchat);
    inputChat->clear();
    QListWidgetItem *lastItem = chat->item(chat->count() - 1);
    if (lastItem) {
        chat->scrollToItem(lastItem);
    }
}
void Lobby::empezar(){
    this->hide();
    Game game(*skt);
    game.loadMap();
    game.run();
    this->close();
}
void Lobby::update(){
    QListWidget* chat = findChild<QListWidget*>("chat");
    int val;
    bool result = my_queue.try_pop(val);
    if(result){
        chat->addItem("lei algo");
        QListWidgetItem *lastItem = chat->item(chat->count() - 1);
        if (lastItem) {
            chat->scrollToItem(lastItem);
        }
        waiter.join();
        this->empezar();
    }
}
void Lobby::start(){
    waiter.start();
    timer.start(500);
}
void Lobby::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
        this->enviar();
    }
}
void Lobby::connectEvents() {
    QPushButton* buttonEnviar = findChild<QPushButton*>("buttonEnviar");
    QObject::connect(buttonEnviar, &QPushButton::clicked,
                     this, &Lobby::enviar);
    QPushButton* buttonEmpezar = findChild<QPushButton*>("buttonEmpezar");
    QObject::connect(buttonEmpezar, &QPushButton::clicked,
                     this, &Lobby::empezar);
    QObject::connect(&timer,&QTimer::timeout,this,&Lobby::update); 
}