#include "../include/editingWindow.h"
#include "ui_editingWindow.h"

EditingWindow::EditingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditingWindow)
{
    ui->setupUi(this);
}

void EditingWindow::setPrev(QWidget *prev)
{
    this->prev = prev;
}

void EditingWindow::setLable(const std::string &text)
{
    ui->label->setText(text.c_str());
}


void EditingWindow::onGoBackBtnClicked()
{
    this->close();
    prev->show();
}


EditingWindow::~EditingWindow()
{
    delete ui;
}
