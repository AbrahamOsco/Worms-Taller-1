#include "../include/chooseMapToEdit.h"
#include "ui_chooseMapToEdit.h"
#include <QScreen>
#include <yaml-cpp/yaml.h>

ChooseMapToEdit::ChooseMapToEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMapToEdit) {
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    this->setAttribute(Qt::WA_DeleteOnClose);

    YAML::Node node = YAML::LoadFile("../Stages/StageNames.yaml");
    for (YAML::const_iterator it = node["namesScenarios"].begin();
                        it != node["namesScenarios"].end(); ++it) {
        const YAML::Node& map  = *it;
        auto name = map["name"].as<std::string>();
        ui->mapNameList->addItem(name.c_str());
    }
}

void ChooseMapToEdit::setPrev(QWidget *prev) {
    this->prev = prev;
}

ChooseMapToEdit::~ChooseMapToEdit() {
    delete ui;
}

void ChooseMapToEdit::onGoBackBtnClicked() {
    this->close();
    prev->show();
}

void ChooseMapToEdit::onConfirmBtnClicked() {
    this->hide();
    std::string text(ui->mapNameList->currentItem()->text().toStdString());
    auto*  ew  = new EditingWindow(nullptr, text);
    ew->setPrev(this);
    ew->loadMapToEdit();
    ew->show();
}
