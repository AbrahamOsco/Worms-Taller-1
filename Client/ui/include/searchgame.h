#ifndef SEARCHGAME_H
#define SEARCHGAME_H

#include <QWidget>
#include <vector>
#include <string>
#include "../../../Common/Socket/Socket.h"
#include "lobby.h"
#include "../../../Common/DTO/RoomDTO.h"

struct GameInfo{
    std::string name;
    std::string mapa;
    size_t players;
    size_t capacity;
};

class SearchGame : public QWidget {
 private:
    Socket* skt;
    std::vector<RoomDTO> gameRooms;
    Lobby lobby;
 public:
    explicit SearchGame(QWidget *parent = 0, Socket* socket = 0);
    void search(const std::vector<RoomDTO> &gameRooms);
 private:
    void join();
    void showInfo();
    void exit();
    void connectEvents();
    void resizeEvent(QResizeEvent* event) override;
};
#endif
