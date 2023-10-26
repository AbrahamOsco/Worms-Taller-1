#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <memory>
#include "mainmenu.h"

class Login : public QWidget {
    private:
    std::unique_ptr<MainMenu> mainmenu;
public:
    explicit Login(QWidget *parent = 0);
private:
    void updateLogin();
    void connectEvents();
    void exit();
};
#endif 
