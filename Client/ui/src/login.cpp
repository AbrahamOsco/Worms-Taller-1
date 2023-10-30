#include "login.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_login.h"
#include <unistd.h>
#include <memory>
#include "mainmenu.h"
#include "liberror.h"

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
    if(name.size() > 0){
        try{
            mainmenu = std::unique_ptr<MainMenu>(new MainMenu(nullptr,server.data(),port.data(),name.data()));
            this->hide();
            mainmenu->show();
        }
        catch (const LibError &e){
            QString update = QString("No fue posible conectarse al: \n Servidor: %1 \n Puerto: %2 \n").arg(qserver,qport);
            labelOut->setText(update);
        }
    } else {
        QString update = QString("Debe ingresar un nombre\n para unirse al servidor\n");
        labelOut->setText(update);
    }
}
void Login::exit(){
    this->close();
}
void Login::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
        this->updateLogin();
    }
}
void Login::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonConnect = findChild<QPushButton*>("buttonLogin");
    QObject::connect(buttonConnect, &QPushButton::clicked,
                     this, &Login::updateLogin);
    QPushButton* buttonSalir = findChild<QPushButton*>("buttonExit");
    QObject::connect(buttonSalir, &QPushButton::clicked,
                     this, &Login::exit);
}
