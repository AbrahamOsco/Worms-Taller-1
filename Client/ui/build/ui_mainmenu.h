/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonCrear;
    QPushButton *buttonUnirse;
    QPushButton *buttonConfig;
    QPushButton *buttonSalir;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainMenu->resize(317, 440);
        widget = new QWidget(MainMenu);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 40, 202, 321));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        buttonCrear = new QPushButton(widget);
        buttonGroup = new QButtonGroup(MainMenu);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(buttonCrear);
        buttonCrear->setObjectName(QString::fromUtf8("buttonCrear"));

        verticalLayout_2->addWidget(buttonCrear);

        buttonUnirse = new QPushButton(widget);
        buttonGroup->addButton(buttonUnirse);
        buttonUnirse->setObjectName(QString::fromUtf8("buttonUnirse"));

        verticalLayout_2->addWidget(buttonUnirse);

        buttonConfig = new QPushButton(widget);
        buttonGroup->addButton(buttonConfig);
        buttonConfig->setObjectName(QString::fromUtf8("buttonConfig"));

        verticalLayout_2->addWidget(buttonConfig);

        buttonSalir = new QPushButton(widget);
        buttonGroup->addButton(buttonSalir);
        buttonSalir->setObjectName(QString::fromUtf8("buttonSalir"));

        verticalLayout_2->addWidget(buttonSalir);


        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QWidget *MainMenu)
    {
        MainMenu->setWindowTitle(QCoreApplication::translate("MainMenu", "MainWindow", nullptr));
        buttonCrear->setText(QCoreApplication::translate("MainMenu", "Crear una Partida", nullptr));
        buttonUnirse->setText(QCoreApplication::translate("MainMenu", "Unirse a Partida", nullptr));
        buttonConfig->setText(QCoreApplication::translate("MainMenu", "Configuraci\303\263n", nullptr));
        buttonSalir->setText(QCoreApplication::translate("MainMenu", "Salir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
