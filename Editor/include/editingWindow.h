#ifndef EDITINGWINDOW_H
#define EDITINGWINDOW_H

#include <QWidget>
#include  <QGraphicsRectItem>
#include <vector>

namespace Ui {
class EditingWindow;
}

class EditingWindow : public QWidget
{
    Q_OBJECT

private slots:
    void onGoBackBtnClicked();

    void on_addWormBtn_clicked();

    void on_addBeamBtn_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

public:
    explicit EditingWindow(QWidget *parent = nullptr);
    void setPrev(QWidget* prev);
    void setLable(const std::string& text);
    ~EditingWindow();

private:
    Ui::EditingWindow *ui;
    QWidget *prev;
    QGraphicsScene *scene;
    std::vector<QGraphicsRectItem*> worms;
    std::vector<QGraphicsRectItem*> beams;
    int newBeamLength;
    QGraphicsRectItem* limits;
};

#endif // EDITINGWINDOW_H
