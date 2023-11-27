#ifndef MAINMENU_H  // NOLINT
#define MAINMENU_H

#include <QWidget>
#include <QPixmap>
#include <string>
#include "./creategame.h"
#include "./searchgame.h"
#include "./socket.h"


class MainMenu : public QWidget {
 private:
    Socket socket;
    std::string playerName;
    CreateGame create;
    SearchGame search;
    QPixmap pixmap;

 public:
    explicit MainMenu(QWidget *parent = 0, char* server = 0, char* data = 0, char* name = 0);
 private:
    void createGame();
    void searchGame();
    void exit();
    void connectEvents();
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // NOLINT
