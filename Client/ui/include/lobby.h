#ifndef LOBBY_H  // NOLINT
#define LOBBY_H

#include <QWidget>
#include <QKeyEvent>
#include <QMovie>
#include <QtMultimedia/QMediaPlayer>
#include <QSound>
#include <QAudioOutput>
#include <QTimer>
#include "../../../Common/Socket/Socket.h"
#include "../../../Common/Queue/Queue.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"
#include "./waiter.h"


class Lobby : public QWidget {
 private:
    Socket* skt;
    QTimer timer;
    Queue<ResolverInitialDTO> my_queue;
    Waiter waiter;
    QMovie gif;
    QSound song;

 public:
    explicit Lobby(QWidget *parent = 0, Socket* socket = 0);
    void start();
 private:
    void empezar();
    void update();
    void play();
    void stop();
    void connectEvents();
};
#endif  // NOLINT
