#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QKeyEvent>
#include "socket.h"
#include <QTimer>
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "waiter.h"
#include <QMovie>
#include <QtMultimedia/QMediaPlayer>
#include <QSound>
 #include <QAudioOutput>

class Lobby : public QWidget {
private:
    Socket* skt;
    QTimer timer;
    Queue<ResolverInitialDTO> my_queue;
    Waiter waiter;
    QMovie gif;
    QSound song;

public:
    explicit Lobby(QWidget *parent = 0,Socket* socket = 0);
    void start();
private:
    void empezar();
    void update();
    void play();
    void stop();
    void connectEvents();
};
#endif