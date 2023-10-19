/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *inputServer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *inputPort;
    QSpacerItem *verticalSpacer_2;
    QPushButton *buttonLogin;
    QStatusBar *statusbar;
    QLabel *labelConnection;
    QPushButton *buttonExit;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(317, 440);
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(30, 20, 249, 242));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 229, 222));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(13, 56, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        inputServer = new QLineEdit(layoutWidget);
        inputServer->setObjectName(QString::fromUtf8("inputServer"));

        horizontalLayout_2->addWidget(inputServer);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        inputPort = new QLineEdit(layoutWidget);
        inputPort->setObjectName(QString::fromUtf8("inputPort"));

        horizontalLayout_3->addWidget(inputPort);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonLogin = new QPushButton(layoutWidget);
        buttonLogin->setObjectName(QString::fromUtf8("buttonLogin"));

        verticalLayout->addWidget(buttonLogin);

        statusbar = new QStatusBar(Login);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(30, 20, 3, 22));
        labelConnection = new QLabel(Login);
        labelConnection->setObjectName(QString::fromUtf8("labelConnection"));
        labelConnection->setGeometry(QRect(40, 290, 241, 101));
        buttonExit = new QPushButton(Login);
        buttonExit->setObjectName(QString::fromUtf8("buttonExit"));
        buttonExit->setGeometry(QRect(110, 410, 81, 28));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:14pt;\">Server</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        inputServer->setToolTip(QCoreApplication::translate("Login", "<html><head/><body><p>IP del servidor</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("Login", "<html><head/><body><p><span style=\" font-size:14pt;\">Port</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        inputPort->setToolTip(QCoreApplication::translate("Login", "<html><head/><body><p>PORT del servidor</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonLogin->setText(QCoreApplication::translate("Login", "Connect", nullptr));
        labelConnection->setText(QCoreApplication::translate("Login", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt;\">Waiting for input</span></p></body></html>", nullptr));
        buttonExit->setText(QCoreApplication::translate("Login", "Salir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
