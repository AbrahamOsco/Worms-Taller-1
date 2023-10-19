#include "login.h"
// Cargo el archivo generado por uic, leer el CMakelist.txt para mas info
#include "ui_login.h"

Login::Login(QWidget *parent) : QWidget(parent) {
    // Instancio la configuracion generada por el designer y uic
    Ui::Login login;
    // Configuro este widget para use esa configuracion
    login.setupUi(this);
    connectEvents();
}

void Login::updateLogin() {
    /**
     * findChild es un metodo de qObject que permite buscar un widget hijo
     * segun su nombre. Si observamos el codigo generado en ui_Greeter
     * cada uno de los objetos recibe un nombre mediante la funcion
     * setObjectName(QString nombre)
     **/
    QLineEdit* inputServer = findChild<QLineEdit*>("inputServer");
    QLineEdit* inputPort = findChild<QLineEdit*>("inputPort");
    QLabel* labelOut = findChild<QLabel*>("labelConnection");
    QString server = inputServer->text();
    QString port = inputPort->text();
    QByteArray serverArray = server.toUtf8();
    QByteArray portArray = port.toUtf8();
    const char* serverChar = serverArray.constData();
    const char* portChar = portArray.constData();
    QString update = QString("Conectandose al servidor %1 \n puerto %2...").arg(server,port);
    labelOut->setText(update);
}

void Login::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonGreet = findChild<QPushButton*>("buttonLogin");
    QObject::connect(buttonGreet, &QPushButton::clicked,
                     this, &Login::updateLogin);
}
