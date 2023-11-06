#include "../include/editingWindow.h"
#include "ui_editingWindow.h"

#include <iostream>
#include <QMessageBox>
#include <QtMath>
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

#define FIXED_WORLD_SIZE_M 60
#define PIX_PER_M 60
#define BEAM_HEIGHT 24
#define WORM_SIZE 30
#define LONG_BEAM 6
#define LONG_BEAM_IMG "longBeam.png"
#define SHORT_BEAM_IMG "shortBeam.png"
#define BG_IMG "bg.png"
#define WORM_IMG "worm.png"

EditingWindow::EditingWindow(QWidget *parent,const std::string& mapName) :
    QWidget(parent),
    ui(new Ui::EditingWindow),
    scene(nullptr),
    newBeamLength(LONG_BEAM_IMG),
    mapName(mapName)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->label->setText(mapName.c_str());
    getFileName(mapName);
    scene  =  new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    std::string bgImg("../Editor/resources/" + std::string(BG_IMG));
    scene->addPixmap(QPixmap(bgImg.c_str()));
    zoom = new Zoom(ui->graphicsView);
    ui->spinBox->setRange(0,170); // angulo de las vigas de 0 a 170
    ui->spinBox->setSingleStep(10); // van de 10 en 10
}

void EditingWindow::setPrev(QWidget *prev)
{
    this->prev = prev;
}

void EditingWindow::loadMapToEdit()
{
    YAML::Node mapNode = YAML::LoadFile("../Stages/" +  mapFileName);
    auto height = mapNode["height"].as<float>();
    YAML::Node beamsNode = mapNode["beams"];
    YAML::Node wormsNode = mapNode["worms"];
    for (YAML::const_iterator it = beamsNode.begin(); it != beamsNode.end(); ++it) {
        const YAML::Node& beamNode = *it;
        auto length = static_cast<int>(beamNode["length"].as<float>());
        auto angle = static_cast<int>(beamNode["angle"].as<float>());

        /* si box2d trabajamos con y negativas:
        auto posX = beamNode["x"].as<float>() * PIX_PER_M;
        auto posY = - (beamNode["y"].as<float>() * PIX_PER_M);
        */

        auto posX = beamNode["x"].as<float>() * PIX_PER_M;
        auto posY = (height - (beamNode["y"].as<float>())) * PIX_PER_M;

        if(length == LONG_BEAM){
            newBeamLength  = LONG_BEAM_IMG;
        } else {
            newBeamLength  = SHORT_BEAM_IMG;
        }

        std::string beamImg("../Editor/resources/" + newBeamLength);
        QGraphicsPixmapItem* beam = scene->addPixmap(QPixmap(beamImg.c_str()));
        beam->setPos(translatedPos(QPointF(posX,posY),angle,length*PIX_PER_M,BEAM_HEIGHT,CENTER_TO_VERTIX));
        beam->setFlag(QGraphicsItem::ItemIsMovable);
        beam->setFlag(QGraphicsItem::ItemIsSelectable);
        beam->setRotation(translatedRotation(angle));
        beams.push_back(beam);
    }

    for (YAML::const_iterator it = wormsNode.begin(); it != wormsNode.end(); ++it) {
        const YAML::Node& wormNode = *it;

        /* si box2d trabajamos con y negativas:
        auto posX = wormNode["positionX"].as<float>() * PIX_PER_M;
        auto posY = - (wormNode["positionY"].as<float>() * PIX_PER_M);
        */

        auto posX = wormNode["positionX"].as<float>() * PIX_PER_M;
        auto posY = (height - (wormNode["positionY"].as<float>())) * PIX_PER_M;

        std::string wormImg("../Editor/resources/" + std::string(WORM_IMG));
        QGraphicsPixmapItem* worm = scene->addPixmap(QPixmap(wormImg.c_str()));
        worm->setPos(translatedPos(QPointF(posX,posY),0,WORM_SIZE,WORM_SIZE,CENTER_TO_VERTIX));
        worm->setFlag(QGraphicsItem::ItemIsMovable);
        worm->setFlag(QGraphicsItem::ItemIsSelectable);
        worms.push_back(worm);
    }
}

int EditingWindow::translatedRotation(int rot)
{
    int tRot = rot;
    if (rot != 0)
    {
        tRot = 180 - rot;
    }
    return tRot;
}

QPointF EditingWindow::translatedPos(const QPointF& pos, int angle, int length, int height, TranslationType factor){
    float posX = pos.x();
    float posY = pos.y();

    if(angle == 0){
        posY = posY - ((height/2)*factor);
        posX = posX - ((length/2)*factor);
    } else if(angle == 90){
        posY = posY - ((length/2)*factor);
        posX = posX + ((height/2)*factor);
    } else if(angle < 90){
        float hip = qSqrt(qPow((height/2),2)+qPow(length/2,2));
        float ang = angle + qRadiansToDegrees(qAtan((height/2)/(length/2)));
        posY = posY - ((qSin(qDegreesToRadians(ang))*hip)*factor);
        posX = posX + ((qCos(qDegreesToRadians(ang))*hip)*factor);
    } else if(angle > 90){
        float hip = qSqrt(qPow((height/2),2)+qPow(length/2,2));
        float ang = translatedRotation(angle) - qRadiansToDegrees(qAtan((height/2)/(length/2)));
        posY = posY - ((qSin(qDegreesToRadians(ang))*hip)*factor);
        posX = posX - ((qCos(qDegreesToRadians(ang))*hip)*factor);
    }

    return(QPointF(posX,posY));
}

void EditingWindow::getFileName(const std::string& mapName)
{
    mapFileName = mapName;
    mapFileName.erase(std::remove(mapFileName.begin(), mapFileName.end(), ' '), mapFileName.end());
    mapFileName += ".yaml";
}

void EditingWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to quit?\nYou might have unsaved changes.", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void EditingWindow::onGoBackBtnClicked()
{
    this->close();
    prev->show();
}

void EditingWindow::onSaveBtnClicked()
{
    YAML::Node node;
    if (std::filesystem::exists("../Stages/" + mapFileName)){
        node = YAML::LoadFile("../Stages/" +  mapFileName);
        node.remove("beams");
        node.remove("worms");
    } else {
        YAML::Node namesNode = YAML::LoadFile("../Stages/StageNames.yaml");
        YAML::Node nameNode;
        nameNode["name"] = mapName;

        namesNode["namesScenarios"].push_back(nameNode);
        std::ofstream foutNames("../Stages/StageNames.yaml");
        foutNames << namesNode;

        node["name"] = mapName;
        node["height"] = FIXED_WORLD_SIZE_M;
        node["width"] = FIXED_WORLD_SIZE_M;
    }

    for (auto & worm : worms) {

        if (worm->isVisible()) {
            YAML::Node wormNode;
            QPointF pos = translatedPos(worm->pos(),0,WORM_SIZE,WORM_SIZE,VERTIX_TO_CENTER);
            wormNode["positionX"] = pos.x()/PIX_PER_M;
            wormNode["positionY"] = node["height"].as<float>() - (pos.y()/PIX_PER_M);

            node["worms"].push_back(wormNode);
        }
    }

    for (auto & beam : beams) {

        if (beam->isVisible()) {
            YAML::Node beamNode;
            QPointF pos = translatedPos(beam->pos(),translatedRotation(beam->rotation()),static_cast<int>(beam->boundingRect().width()),BEAM_HEIGHT,VERTIX_TO_CENTER);
            beamNode["x"] = pos.x()/PIX_PER_M;
            beamNode["y"] = node["height"].as<float>() - (pos.y()/PIX_PER_M);
            beamNode["angle"] = translatedRotation(beam->rotation());
            beamNode["length"] = static_cast<int>(beam->boundingRect().width()/PIX_PER_M);

            node["beams"].push_back(beamNode);
        }
    }


    std::ofstream fout("../Stages/" + mapFileName);
    fout << node;

}

void EditingWindow::onAddWormBtnClicked()
{
    std::string wormImg("../Editor/resources/" + std::string(WORM_IMG));
    QGraphicsPixmapItem* worm = scene->addPixmap(QPixmap(wormImg.c_str()));
    worm->setFlag(QGraphicsItem::ItemIsMovable);
    worm->setFlag(QGraphicsItem::ItemIsSelectable);
    worm->setPos(ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center()));
    worms.push_back(worm);
}


void EditingWindow::onAddBeamBtnClicked()
{
    GetSelectedBeamLength();
    std::string beamImg("../Editor/resources/" + newBeamLength);
    QGraphicsPixmapItem* beam = scene->addPixmap(QPixmap(beamImg.c_str()));
    beam->setFlag(QGraphicsItem::ItemIsMovable);
    beam->setFlag(QGraphicsItem::ItemIsSelectable);
    beam->setRotation(translatedRotation(ui->spinBox->value()));
    beam->setPos(ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center()));
    beams.push_back(beam);
}


void EditingWindow::GetSelectedBeamLength()
{
    if (ui->lenComboBox->currentText() == "Short") {
        newBeamLength  = SHORT_BEAM_IMG;
    } else if (ui->lenComboBox->currentText() == "Long") {
        newBeamLength  = LONG_BEAM_IMG;
    }
}


void EditingWindow::onDeleteBtnClicked()
{
    auto list  = scene->selectedItems();
    for(int i = 0; i<list.count(); i++){
        (list[i])->hide();
    }
}


EditingWindow::~EditingWindow()
{
    delete ui;
    for (auto & worm : worms) {
        delete worm;
    }
    for (auto & beam : beams) {
        delete beam;
    }
}
