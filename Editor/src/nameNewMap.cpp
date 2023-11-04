#include "../include/nameNewMap.h"
#include "ui_nameNewMap.h"
#include <yaml-cpp/yaml.h>

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
    std::string newName = ui->mapNameInput->text().toStdString();
    bool nameIsAvailable = true;
    YAML::Node node = YAML::LoadFile( "../Stages/StageNames.yaml");
    for (YAML::const_iterator it = node["namesScenarios"].begin(); it != node["namesScenarios"].end(); ++it){
        const YAML::Node& map  = *it;
        auto name = map["name"].as<std::string>();
        std::string nameNoSpaces(name);
        nameNoSpaces.erase(std::remove(nameNoSpaces.begin(), nameNoSpaces.end(), ' '), nameNoSpaces.end());
        if (name == newName ||
            nameNoSpaces == newName){
            ui->mapNameFailLable->setText("A map already exists with this name.\nPlease pick a different one.");
            nameIsAvailable = false;
            break;
        }

    }

    if (nameIsAvailable){
        this->hide();
        std::string text(newName);
        auto*  ew  = new EditingWindow(nullptr,text);
        ew->setPrev(this);
        ew->show();
    }
}
