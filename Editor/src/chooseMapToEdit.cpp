#include "../include/chooseMapToEdit.h"
#include "ui_chooseMapToEdit.h"
#include <QScreen>
#include <yaml-cpp/yaml.h>

ChooseMapToEdit::ChooseMapToEdit(QWidget *parent) :
    QWidget(parent),
    ui() {
    ui.setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());

    YAML::Node node = YAML::LoadFile("../Stages/StageNames.yaml");
    for (YAML::const_iterator it = node["namesScenarios"].begin();
                        it != node["namesScenarios"].end(); ++it) {
        const YAML::Node& map  = *it;
        auto name = map["name"].as<std::string>();
        ui.mapNameList->addItem(name.c_str());
    }
}

ChooseMapToEdit::~ChooseMapToEdit() = default;

void ChooseMapToEdit::onConfirmBtnClicked() {
    this->hide();
    std::string text(ui.mapNameList->currentItem()->text().toStdString());
    ew = std::unique_ptr<EditingWindow>(new EditingWindow(nullptr, text));
    ew->loadMapToEdit();
    ew->show();
}
