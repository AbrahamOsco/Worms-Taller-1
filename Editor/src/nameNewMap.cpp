#include "../include/nameNewMap.h"
#include "ui_nameNewMap.h"
#include <QScreen>
#include <yaml-cpp/yaml.h>

NameNewMap::NameNewMap(QWidget *parent) :
    QWidget(parent), ui() {
    ui.setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
}

NameNewMap::~NameNewMap() = default;

void NameNewMap::onConfirmBtnClicked() {
    std::string newName = ui.mapNameInput->text().toStdString();
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
            ui.mapNameFailLable->setText("A map already exists with this name."
                                          "\nPlease pick a different one.");
            nameIsAvailable = false;
            break;
        }
    }

    if (nameIsAvailable) {
        this->hide();
        const std::string& text(newName);
        ew  = std::unique_ptr<EditingWindow>(new EditingWindow(nullptr, text));
        ew->show();
    }
}
