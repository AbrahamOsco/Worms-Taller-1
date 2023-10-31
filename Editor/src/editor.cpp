#include "../include/editor.h"
#include "./ui_editor.h"

Editor::Editor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}


void Editor::on_createMapBtn_clicked()
{
    this->hide();
    auto* nnm  = new NameNewMap;
    nnm->setPrev(this);
    nnm->show();
}


void Editor::on_editMapBtn_clicked()
{
    this->hide();
    auto* cmte = new ChooseMapToEdit;
    cmte->setPrev(this);
    cmte->show();
}

