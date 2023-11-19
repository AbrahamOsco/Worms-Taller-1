#include "../include/editor.h"
#include <QScreen>
#include "./ui_editor.h"


Editor::Editor(QWidget *parent)
    : QWidget(parent)
    , ui() {
    ui.setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
}

Editor::~Editor() = default;


void Editor::on_createMapBtn_clicked() {
    this->hide();
    nnm =  std::unique_ptr<NameNewMap>(new NameNewMap(nullptr));
    nnm->show();
}


void Editor::on_editMapBtn_clicked() {
    this->hide();
    cmte = std::unique_ptr<ChooseMapToEdit>(new ChooseMapToEdit(nullptr));
    cmte->show();
}

