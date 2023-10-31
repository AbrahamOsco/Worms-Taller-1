#include "../include/editingWindow.h"
#include "ui_editingWindow.h"

EditingWindow::EditingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditingWindow),
    scene(nullptr),
    newBeamLength(60)

{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    scene  =  new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    limits = scene->addRect(0,0,500,300,QPen(Qt::red));
    ui->spinBox->setRange(0,180);
    ui->spinBox->setSingleStep(10);
    ui->heightValueBox->setRange(1,999);
    ui->widthValueBox->setRange(1,999);
    ui->heightValueBox->setValue(300);
    ui->widthValueBox->setValue(500);
}

void EditingWindow::setPrev(QWidget *prev)
{
    this->prev = prev;
}

void EditingWindow::setLable(const std::string &text)
{
    ui->label->setText(text.c_str());
}


void EditingWindow::onGoBackBtnClicked()
{
    this->close();
    prev->show();
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

void EditingWindow::on_addWormBtn_clicked()
{
    QGraphicsRectItem* worm = scene->addRect(0,0,10,10);
    worm->setFlag(QGraphicsItem::ItemIsMovable);
    worm->setFlag(QGraphicsItem::ItemIsSelectable);
    worms.push_back(worm);
}


void EditingWindow::on_addBeamBtn_clicked()
{
    QGraphicsRectItem* beam = scene->addRect(0,0,newBeamLength,8);
    beam->setFlag(QGraphicsItem::ItemIsMovable);
    beam->setFlag(QGraphicsItem::ItemIsSelectable);
    beam->setRotation(ui->spinBox->value());
    beams.push_back(beam);
}


void EditingWindow::on_pushButton_2_clicked()
{
    if (ui->pushButton_2->text() == "long") {
        ui->pushButton_2->setText("short");
        newBeamLength  = 30;
    } else if (ui->pushButton_2->text() == "short") {
        ui->pushButton_2->setText("long");
        newBeamLength  = 60;
    }
}


void EditingWindow::on_pushButton_3_clicked()
{
    auto list  = scene->selectedItems();
    for(int i = 0; i<list.count(); i++){
        scene->removeItem(list[i]);
    }
}


void EditingWindow::on_pushButton_4_clicked()
{
    scene->removeItem(limits);
    QGraphicsRectItem* newLimits = scene->addRect(limits->pos().x(),limits->pos().y(),ui->widthValueBox->value(),ui->heightValueBox->value(),QPen(Qt::red));
    limits = newLimits;
}

