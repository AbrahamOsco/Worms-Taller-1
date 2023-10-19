#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

class Login : public QWidget {
public:
    explicit Login(QWidget *parent = 0);
private:
    void updateLogin();
    void connectEvents();
    void exit();
};
#endif 
