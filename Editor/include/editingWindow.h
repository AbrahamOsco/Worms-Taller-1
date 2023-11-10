#ifndef EDITINGWINDOW_H
#define EDITINGWINDOW_H

#include <QWidget>
#include  <QGraphicsRectItem>
#include <QCloseEvent>
#include <vector>
#include  <string>
#include "../include/zoom.h"

namespace Ui {
class EditingWindow;
}

class EditingWindow : public QWidget {
    Q_OBJECT

 private slots:
    void onGoBackBtnClicked();

    void onAddWormBtnClicked();

    void onAddBeamBtnClicked();

    void onDeleteBtnClicked();

    void onSaveBtnClicked();

    void onSpinBoxEdited();

    void onBgComboBoxChanged();


 public:
    explicit EditingWindow(QWidget *parent = nullptr,
                           const std::string& mapName = "");
    void setPrev(QWidget* prev);
    void loadMapToEdit();
    ~EditingWindow() override;

 private:
    Ui::EditingWindow *ui;
    Zoom* zoom;
    QWidget* prev;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *bg;
    std::vector<QGraphicsPixmapItem*> worms;
    std::vector<QGraphicsPixmapItem*> beams;
    std::string newBeamLength;
    std::string mapName;
    std::string mapFileName;
    enum TranslationType {VERTEX_TO_CENTER = -1, CENTER_TO_VERTEX = 1};
    static QPointF translatedPos(const QPointF& pos, QGraphicsPixmapItem* item,
                          TranslationType factor);
    void getFileName(const std::string& mapName);
    void closeEvent(QCloseEvent *event) override;
    void GetSelectedBeamLength();
    bool hasAtLeastOneWorm();
    void removeItemsOutsideBounds();
    bool hasOverlappingWorms();
    void manageOverlappingWorms();
};

#endif  // EDITINGWINDOW_H
