#ifndef EDITINGWINDOW_H
#define EDITINGWINDOW_H

#include "../include/zoom.h"
#include <QWidget>
#include  <QGraphicsRectItem>
#include <QCloseEvent>
#include <vector>
#include  <string>

namespace Ui {
class EditingWindow;
}

class EditingWindow : public QWidget
{
    Q_OBJECT

private slots:
    void onGoBackBtnClicked();

    void onAddWormBtnClicked();

    void onAddBeamBtnClicked();

    void onChangeLenBtnClicked();

    void onDeleteBtnClicked();

    void onSaveBtnClicked();


public:
    explicit EditingWindow(QWidget *parent = nullptr,const std::string& mapName = "");
    void setPrev(QWidget* prev);
    void loadMapToEdit();
    ~EditingWindow();

private:
    Ui::EditingWindow *ui;
    Zoom *zoom;
    QWidget *prev;
    QGraphicsScene *scene;
    std::vector<QGraphicsPixmapItem*> worms;
    std::vector<QGraphicsPixmapItem*> beams;
    std::string newBeamLength;
    std::string mapName;
    std::string mapFileName;
    int translatedRotation(int rot);
    enum TranslationType {VERTIX_TO_CENTER = -1, CENTER_TO_VERTIX = 1};
    QPointF translatedPos(const QPointF& pos, int angle, int length, int height, TranslationType factor);
    void getFileName(const std::string& mapName);
    void closeEvent(QCloseEvent *event);
};

#endif // EDITINGWINDOW_H
