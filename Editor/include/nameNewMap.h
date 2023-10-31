#ifndef NAMENEWMAP_H
#define NAMENEWMAP_H

#include <QWidget>
#include "editingWindow.h"

namespace Ui {
class NameNewMap;
}

class NameNewMap : public QWidget
{
    Q_OBJECT

public:
    explicit NameNewMap(QWidget *parent = nullptr);
    void setPrev(QWidget *prev);
    ~NameNewMap();

private slots:
    void onGoBackBtnClicked();
    void onConfirmBtnClicked();

private:
    Ui::NameNewMap *ui;
    QWidget *prev;
};

#endif // NAMENEWMAP_H
