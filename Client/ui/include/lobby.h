#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QKeyEvent>
#include "socket.h"
#include <QTimer>

class Lobby : public QWidget {
private:
    Socket* skt;
    QTimer timer;
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