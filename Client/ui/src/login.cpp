#include "../include/login.h"
#include <QPixmap>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <unistd.h>
#include <memory>
#include "ui_login.h"  // NOLINT
#include "../include/mainmenu.h"
#include "../../../Common/Socket/LibError.h"


Login::Login(QWidget *parent) : QWidget(parent) {
    Ui::Login login;
    login.setupUi(this);
    connectEvents();
}

void Login::updateLogin() {
    QLineEdit* inputServer = findChild<QLineEdit*>("inputServer");
    QLineEdit* inputPort = findChild<QLineEdit*>("inputPort");
    QLineEdit* inputName = findChild<QLineEdit*>("inputName");
    QLabel* labelOut = findChild<QLabel*>("labelConnection");
    QString qserver = inputServer->text();
    QString qport = inputPort->text();
    QString qname = inputName->text();
    std::string server = qserver.toStdString();
    std::string port = qport.toStdString();
    std::string name = qname.toStdString();
    if (name.size() > 0) {
        try {
            mainmenu = std::unique_ptr<MainMenu>(new MainMenu(nullptr, server.data(), port.data(), name.data()));
            this->hide();
            mainmenu->show();
        } catch (const LibError &e) {
            QString update = QString("No fue posible conectarse al: \n Servidor: %1 \n Puerto: %2 \n").
                                arg(qserver, qport);
            labelOut->setText(update);
        }
    } else {
        QString update = QString("Debe ingresar un nombre\n para unirse al servidor\n");
        labelOut->setText(update);
    }
}
void Login::exit() {
    this->close();
}
void Login::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        this->updateLogin();
    }
}
void Login::resizeEvent(QResizeEvent* event) {
    QLabel* back = findChild<QLabel*>("labelBackground");
    back->resize(event->size().width(), event->size().height());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout * layout = findChild<QVBoxLayout*>("verticalLayout");
    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
}
void Login::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonConnect = findChild<QPushButton*>("buttonLogin");
    QObject::connect(buttonConnect, &QPushButton::clicked,
                     this, &Login::updateLogin);
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonExit");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &Login::exit);
    QLabel* back = findChild<QLabel*>("labelBackground");
    QPixmap pixmap("../Client/ui/resources/login.png");
    back->setPixmap(pixmap);
    back->setScaledContents(true);
    this->setWindowTitle("Worms");
    QRect screenGeometry = QApplication::desktop()->availableGeometry(this);
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
