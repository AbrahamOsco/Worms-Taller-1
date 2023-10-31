#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QKeyEvent>
#include "socket.h"
#include <QTimer>
#include "../Common/Queue/Queue.h"
#include "waiter.h"

class Lobby : public QWidget {
private:
    Socket* skt;
    QTimer timer;
    Queue<int> my_queue;
    Waiter waiter;

public:
    explicit Lobby(QWidget *parent = 0,Socket* socket = 0);
    void start();
private:
    void enviar();
    void empezar();
    void update();
    void connectEvents();
    void keyPressEvent(QKeyEvent *event) override;
};
#endif