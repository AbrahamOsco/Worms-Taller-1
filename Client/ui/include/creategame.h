#ifndef CREATEGAME_H  // NOLINT
#define CREATEGAME_H

#include <QWidget>
#include <string>
#include <map>
#include <vector>
#include "../../../Common/Socket/Socket.h"
#include "./lobby.h"

class CreateGame : public QWidget {
 private:
    Socket* socket;
    QWidget* my_parent;
    Lobby lobby;
    std::vector<std::string> namesScenarios;
    std::map<std::string, size_t> mapStageMaxWorm;
 public:
    explicit CreateGame(QWidget *parent = 0, Socket* skt = 0);
    void search(const std::vector<std::string> &nameScenarios, std::map<std::string, size_t>& mapStageMaxWorm);  // NOLINT
 private:
    void create();
    void connectEvents();
    void exit();
    void changeMax();
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // NOLINT
