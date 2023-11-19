#ifndef LOGIN_H  // NOLINT
#define LOGIN_H


#include <QWidget>
#include <QKeyEvent>
#include <memory>
#include "./mainmenu.h"

class Login : public QWidget {
 private:
    std::unique_ptr<MainMenu> mainmenu;
 public:
    explicit Login(QWidget *parent = 0);
 private:
    void updateLogin();
    void connectEvents();
    void exit();
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // NOLINT
