#include "../include/nameNewMap.h"
#include "ui_nameNewMap.h"
#include <QScreen>
#include <yaml-cpp/yaml.h>

NameNewMap::NameNewMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NameNewMap) {
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void NameNewMap::setPrev(QWidget *prev) {
    this->prev = prev;
}

NameNewMap::~NameNewMap() {
    delete ui;
}

void NameNewMap::onGoBackBtnClicked() {
    this->close();
    prev->show();
}

void NameNewMap::onConfirmBtnClicked() {
    // check if name is available
    std::string newName = ui->mapNameInput->text().toStdString();
    std::string newNameNoSpaces(newName);
    newNameNoSpaces.erase(std::remove(newNameNoSpaces.begin(),
                                   newNameNoSpaces.end(), ' '),
                                    newNameNoSpaces.end());
    bool nameIsAvailable = true;
    YAML::Node node = YAML::LoadFile("../Stages/StageNames.yaml");
    for (YAML::const_iterator it = node["namesScenarios"].begin();
                        it != node["namesScenarios"].end(); ++it) {
        const YAML::Node& map  = *it;
        auto name = map["name"].as<std::string>();
        std::string nameNoSpaces(name);
        nameNoSpaces.erase(std::remove(nameNoSpaces.begin(),
                                       nameNoSpaces.end(), ' '),
                                        nameNoSpaces.end());
        if (newNameNoSpaces == nameNoSpaces) {
            ui->mapNameFailLable->setText("A map already exists with this name."
                                          "\nPlease pick a different one.");
            nameIsAvailable = false;
            break;
        }
    }

    if (nameIsAvailable) {
        this->hide();
        std::string text(newName);
        auto*  ew  = new EditingWindow(nullptr, text);
        ew->setPrev(this);
        ew->show();
    }
}
