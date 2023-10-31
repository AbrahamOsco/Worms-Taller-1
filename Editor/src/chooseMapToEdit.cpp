#include "../include/chooseMapToEdit.h"
#include "ui_chooseMapToEdit.h"
#include <yaml-cpp/yaml.h>
#include <cstdlib>
#include <linux/limits.h>

ChooseMapToEdit::ChooseMapToEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseMapToEdit)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    char startPathC[PATH_MAX];
    realpath("../../", startPathC);
    std::string startPath(startPathC);
    YAML::Node node = YAML::LoadFile(startPath + "/Stages/StageNames.yaml");
    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it){
        const YAML::Node& map  = *it;
        std::string name = map["name"].as<std::string>();
        ui->mapNameList->addItem(name.c_str());
    }
}

void ChooseMapToEdit::setPrev(QWidget *prev)
{
    this->prev = prev;
}

ChooseMapToEdit::~ChooseMapToEdit()
{
    delete ui;
}

void ChooseMapToEdit::onGoBackBtnClicked()
{
    this->close();
    prev->show();
}

void ChooseMapToEdit::onConfirmBtnClicked()
{
    this->hide();
    auto*  ew  = new EditingWindow;
    std::string text("editing existing map: " + ui->mapNameList->currentItem()->text().toStdString());
    ew->setLable(text);
    ew->setPrev(this);
    ew->show();
}
