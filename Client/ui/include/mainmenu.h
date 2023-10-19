#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class MainMenu : public QWidget {
public:
    explicit MainMenu(QWidget *parent = 0);
private:
    void exit();
    void connectEvents();
};
#endif 
