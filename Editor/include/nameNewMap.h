#ifndef NAMENEWMAP_H
#define NAMENEWMAP_H

#include <QWidget>
#include <memory>
#include "editingWindow.h"
#include "ui_nameNewMap.h"

namespace Ui {
class NameNewMap;
}

class NameNewMap : public QWidget {
    Q_OBJECT

 public:
    explicit NameNewMap(QWidget *parent);
    ~NameNewMap() override;

 private slots:
    void onConfirmBtnClicked();

 private:
    Ui::NameNewMap ui;
    std::unique_ptr<EditingWindow> ew;
};

#endif  // NAMENEWMAP_H
