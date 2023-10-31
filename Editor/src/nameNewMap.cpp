#include "../include/nameNewMap.h"
#include "ui_nameNewMap.h"

NameNewMap::NameNewMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NameNewMap)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void NameNewMap::setPrev(QWidget *prev)
{
    this->prev = prev;
}

NameNewMap::~NameNewMap()
{
    delete ui;
}

void NameNewMap::onGoBackBtnClicked()
{
    this->close();
    prev->show();
}

void NameNewMap::onConfirmBtnClicked()
{
    //check if name is available
    this->hide();
    auto*  ew  = new EditingWindow;
    std::string text("editing new map: " + ui->mapNameInput->text().toStdString());
    ew->setLable(text);
    ew->setPrev(this);
    ew->show();
}
