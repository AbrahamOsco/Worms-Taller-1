#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "chooseMapToEdit.h"
#include "nameNewMap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QWidget {
    Q_OBJECT

 public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

 private slots:
    void on_createMapBtn_clicked();

    void on_editMapBtn_clicked();

 private:
    Ui::Editor *ui;
};
#endif  // EDITOR_H
