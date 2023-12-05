#include "../include/editingWindow.h"
#include "ui_editingWindow.h"

#include <QMessageBox>
#include <QtMath>
#include <QScreen>
#include <yaml-cpp/yaml.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

#define WORLD_HEIGHT 18
#define WORLD_WIDTH 32
#define PIX_PER_M 60
#define ANGLE_KEY 0
#define LENGTH_KEY 1
#define LONG_BEAM 6
#define SHORT_BEAM 3
#define LONG_BEAM_IMG "beams/longBeam"
#define SHORT_BEAM_IMG "beams/shortBeam"
#define WORM_IMG "worm.png"

EditingWindow::EditingWindow(QWidget *parent, const std::string& mapName) :
    QWidget(parent),
    ui(),
    scene(nullptr),
    newBeamLengthImg(LONG_BEAM_IMG),
    mapName(mapName),
    zoom(nullptr) {
    ui.setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());

    ui.label->setText(mapName.c_str());
    getFileName(mapName);

    scene  =  new QGraphicsScene;
    ui.graphicsView->setScene(scene);
    std::string bgImg("../Editor/resources/" + ui.bgComboBox->currentText().toStdString() + ".png");
    bg = scene->addPixmap(QPixmap(bgImg.c_str()));

    zoom = new Zoom(ui.graphicsView);
}

void EditingWindow::loadMapToEdit() {
    YAML::Node mapNode = YAML::LoadFile("../Stages/" +  mapFileName);
    auto bgName = mapNode["background"].as<std::string>();
    std::string bgImg("../Editor/resources/" + bgName + ".png");
    ui.bgComboBox->setCurrentText(bgName.c_str());
    bg->setPixmap(QPixmap(bgImg.c_str()));
    bg->setPixmap(QPixmap(bgImg.c_str()));
    auto height = mapNode["height"].as<double>();
    YAML::Node beamsNode = mapNode["beams"];
    YAML::Node wormsNode = mapNode["worms"];
    for (YAML::const_iterator it = beamsNode.begin();
                        it != beamsNode.end(); ++it) {
        const YAML::Node& beamNode = *it;

        auto length = beamNode["length"].as<double>();
        auto angle = static_cast<int>(beamNode["angle"].as<float>());

        auto posX = beamNode["x"].as<double>() * PIX_PER_M;
        auto posY = (height - (beamNode["y"].as<double>())) * PIX_PER_M;

        if (length == LONG_BEAM) {
            newBeamLengthImg  = LONG_BEAM_IMG;
        } else {
            newBeamLengthImg  = SHORT_BEAM_IMG;
        }

        std::string beamImg("../Editor/resources/" + newBeamLengthImg +
                        std::to_string(angle) + ".png");
        QGraphicsPixmapItem* beam = scene->addPixmap(QPixmap(beamImg.c_str()));
        beam->setPos(translatedPos(QPointF(posX, posY), beam,
                                   CENTER_TO_VERTEX));
        beam->setFlag(QGraphicsItem::ItemIsMovable);
        beam->setFlag(QGraphicsItem::ItemIsSelectable);
        beam->setData(ANGLE_KEY, angle);
        beam->setData(LENGTH_KEY, length);
        beams.push_back(beam);
    }

    for (YAML::const_iterator it = wormsNode.begin();
                        it != wormsNode.end(); ++it) {
        const YAML::Node& wormNode = *it;

        auto posX = wormNode["positionX"].as<double>() * PIX_PER_M;
        auto posY = (height - (wormNode["positionY"].as<double>())) * PIX_PER_M;

        std::string wormImg("../Editor/resources/" + std::string(WORM_IMG));
        QGraphicsPixmapItem* worm = scene->addPixmap(QPixmap(wormImg.c_str()));
        worm->setPos(translatedPos(QPointF(posX, posY), worm,
                                   CENTER_TO_VERTEX));
        worm->setFlag(QGraphicsItem::ItemIsMovable);
        worm->setFlag(QGraphicsItem::ItemIsSelectable);
        worms.push_back(worm);
    }
}

QPointF EditingWindow::translatedPos(const QPointF& pos, QGraphicsPixmapItem* item,
                                     TranslationType factor) {
    auto posX = pos.x();
    auto posY = pos.y();

    posX = posX - (item->boundingRect().width()/2)*factor;
    posY = posY - (item->boundingRect().height()/2)*factor;

    return(QPointF(posX, posY));
}

void EditingWindow::getFileName(const std::string& mapName_) {
    mapFileName = mapName_;
    mapFileName.erase(std::remove(mapFileName.begin(),
                                    mapFileName.end(), ' '),
                                    mapFileName.end());
    mapFileName += ".yaml";
}

void EditingWindow::removeItemsOutsideBounds() {
    std::vector<QGraphicsPixmapItem*> wormsOutsideBounds;
    for (auto & worm : worms) {
        if (!worm->collidesWithItem(bg)) {
            wormsOutsideBounds.push_back(worm);
        }
    }
    for (auto & worm : wormsOutsideBounds) {
        worms.erase(std::remove(worms.begin(), worms.end(), worm),
                        worms.end());
        delete worm;
    }

    std::vector<QGraphicsPixmapItem*> beamsOutsideBounds;
    for (auto & beam : beams) {
        if (!(beam->collidesWithItem(bg))) {
            beamsOutsideBounds.push_back(beam);
        }
    }

    for (auto & beam : beamsOutsideBounds) {
        beams.erase(std::remove(beams.begin(), beams.end(), beam),
                        beams.end());
        delete beam;
    }
}

bool EditingWindow::hasAtLeastOneWorm() {
    bool aWormIsVisible = false;
    for (auto & worm : worms) {
        aWormIsVisible = true;
        break;
    }
    return aWormIsVisible;
}

bool EditingWindow::hasOverlappingWorms() {
    bool overlapping = false;
    for (auto & worm : worms) {
        if (worm->collidingItems().size() > 1) {
            overlapping = true;
            worm->setSelected(true);
        }
    }
    return overlapping;
}

void EditingWindow::manageOverlappingWorms() {
    uint64_t wormsNum = worms.size();
    int start = 0;
    for (int i = 0; i < wormsNum && start < wormsNum; i++) {
        QGraphicsPixmapItem* collidingWorm = nullptr;
        for (auto worm = worms.begin() + start; worm != worms.end(); ++worm) {
            QList collidingItems = (*worm)->collidingItems();
            if (collidingItems.size() > 1) {
                collidingWorm = *worm;
                start--;
                break;
            }
            start++;
        }
        start++;
        if (collidingWorm != nullptr) {
            worms.erase(std::remove(worms.begin(), worms.end(),
                                    collidingWorm), worms.end());
            delete collidingWorm;
        }
    }
}

void EditingWindow::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit",
                                  "Are you sure you want to quit?\n"
                                  "You might have unsaved changes.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void EditingWindow::onSaveBtnClicked() {
    removeItemsOutsideBounds();
    if (hasOverlappingWorms()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning: Your worms overlap!",
                                      "Any worms that overlap beams\n"
                                      "or other worms will be deleted.\n\n"
                                      "Are you sure you want to continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }
    manageOverlappingWorms();
    if (!hasAtLeastOneWorm()) {
        QMessageBox::critical(nullptr, "Not enough worms", "Add at least one worm to save.");
        return;
    }


    YAML::Node node;
    if (std::filesystem::exists("../Stages/" + mapFileName)) {
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
        node["height"] = WORLD_HEIGHT;
        node["width"] = WORLD_WIDTH;
    }

    node["background"] = ui.bgComboBox->currentText().toStdString();

    for (auto & worm : worms) {
        YAML::Node wormNode;
        QPointF pos = translatedPos(worm->pos(), worm,
                                    VERTEX_TO_CENTER);
        wormNode["positionX"] = pos.x()/PIX_PER_M;
        wormNode["positionY"] = node["height"].as<float>() -
                                    (pos.y()/PIX_PER_M);

        node["worms"].push_back(wormNode);
    }

    for (auto & beam : beams) {
        YAML::Node beamNode;
        QPointF pos = translatedPos(beam->pos(), beam,
                                    VERTEX_TO_CENTER);
        beamNode["x"] = pos.x()/PIX_PER_M;
        beamNode["y"] = node["height"].as<float>() - (pos.y()/PIX_PER_M);
        beamNode["angle"] = beam->data(ANGLE_KEY).toInt();
        beamNode["length"] = beam->data(LENGTH_KEY).toInt();
        node["beams"].push_back(beamNode);
    }

    std::ofstream fout("../Stages/" + mapFileName);
    fout << node;
}

void EditingWindow::onAddWormBtnClicked() {
    std::string wormImg("../Editor/resources/" + std::string(WORM_IMG));
    QGraphicsPixmapItem* worm = scene->addPixmap(QPixmap(wormImg.c_str()));
    worm->setFlag(QGraphicsItem::ItemIsMovable);
    worm->setFlag(QGraphicsItem::ItemIsSelectable);
    worm->setPos(ui.graphicsView->mapToScene(
            ui.graphicsView->viewport()->rect().center()));
    worms.push_back(worm);
}


void EditingWindow::onAddBeamBtnClicked() {
    GetSelectedBeamLength();
    std::string beamImg("../Editor/resources/" + newBeamLengthImg +
                    std::to_string(ui.spinBox->value()) + ".png");
    QGraphicsPixmapItem* beam = scene->addPixmap(QPixmap(beamImg.c_str()));
    beam->setFlag(QGraphicsItem::ItemIsMovable);
    beam->setFlag(QGraphicsItem::ItemIsSelectable);
    beam->setData(ANGLE_KEY, ui.spinBox->value());
    beam->setData(LENGTH_KEY, newBeamLengthInt);
    beam->setPos(ui.graphicsView->mapToScene(
            ui.graphicsView->viewport()->rect().center()));
    beams.push_back(beam);
}


void EditingWindow::GetSelectedBeamLength() {
    if (ui.lenComboBox->currentText() == "Short") {
        newBeamLengthImg  = SHORT_BEAM_IMG;
        newBeamLengthInt = SHORT_BEAM;
    } else if (ui.lenComboBox->currentText() == "Long") {
        newBeamLengthImg  = LONG_BEAM_IMG;
        newBeamLengthInt = LONG_BEAM;
    }
}


void EditingWindow::onDeleteBtnClicked() {
    auto list  = scene->selectedItems();
    for (int i = 0; i < list.count(); i++) {
        if (worms.erase(std::remove(worms.begin(), worms.end(), list[i])
                       , worms.end()) == worms.end()) {
            beams.erase(std::remove(beams.begin(), beams.end(), list[i])
                    , beams.end());
        }
        delete list[i];
    }
}

void EditingWindow::onSpinBoxEdited() {
    int value = ui.spinBox->value();
    if (value%10 != 0) {
        ui.spinBox->setValue((value/10)*10);
    }
}

void EditingWindow::onBgComboBoxChanged() {
    std::string bgImg("../Editor/resources/" +
                ui.bgComboBox->currentText().toStdString() + ".png");
    bg->setPixmap(QPixmap(bgImg.c_str()));
}


EditingWindow::~EditingWindow() {
    for (auto & worm : worms) {
        delete worm;
    }
    for (auto & beam : beams) {
        delete beam;
    }
}
