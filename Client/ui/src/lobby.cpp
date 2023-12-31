#include "../include/lobby.h"
#include <QTime>
#include <QMovie>
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <QMediaPlayer>
#include "ui_lobby.h"  // NOLINT
#include "../../../Common/Socket/Socket.h"

#include "../../../Common/Queue/Queue.h"
#include "../../../Common/Thread/Thread.h"
#include "../include/waiter.h"
#include "../../src/game/Game.h"
#include "../../../Common/DTO/ResolverInitialDTO.h"


Lobby::Lobby(QWidget *parent, Socket* socket) : QWidget(parent),
                                                timer(this),
                                                my_queue(200),
                                                skt(socket),
                                                waiter(skt, &my_queue),
                                                gif(QMovie("../Client/ui/resources/waiting.gif")),
                                                song("../Client/ui/resources/home.wav") {
    Ui::Lobby lobby;
    lobby.setupUi(this);
    timer.start(500);
    connectEvents();
}
void Lobby::commence() {
    song.stop();
    this->hide();
    Game game(*skt);
    game.loadMap();
    game.run();
    this->close();
}
void Lobby::update() {
    ResolverInitialDTO val;
    bool result = my_queue.try_pop(val);
    if (result) {
        if (val.getOperationType() == START_GAME) {
            waiter.join();
            this->commence();
        }
        if (val.getOperationType() == END_DTO) {
            waiter.join();
            this->close();
        }
    }
}
void Lobby::start() {
    waiter.start();
    QLabel* labelGif = findChild<QLabel*>("labelGif");
    labelGif->setMovie(&gif);
    gif.start();
    timer.start(500);
}
void Lobby::play() {
    song.play();
}
void Lobby::stop() {
    song.stop();
}
void Lobby::connectEvents() {
    QObject::connect(&timer, &QTimer::timeout, this, &Lobby::update);
    this->setWindowTitle("Worms-Lobby");
    QPushButton* buttonPlay = findChild<QPushButton*>("buttonPlay");
    QObject::connect(buttonPlay, &QPushButton::clicked,
                     this, &Lobby::play);
    QPushButton* buttonStop = findChild<QPushButton*>("buttonStop");
    QObject::connect(buttonStop, &QPushButton::clicked,
                     this, &Lobby::stop);
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}
