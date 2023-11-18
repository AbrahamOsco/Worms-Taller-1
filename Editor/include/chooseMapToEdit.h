#ifndef CHOOSEMAPTOEDIT_H
#define CHOOSEMAPTOEDIT_H

#include <QDialog>
#include "editingWindow.h"
#include "ui_chooseMapToEdit.h"

namespace Ui {
class ChooseMapToEdit;
}

class ChooseMapToEdit : public QWidget {
    Q_OBJECT

 public:
    explicit ChooseMapToEdit(QWidget *parent);
    ~ChooseMapToEdit() override;

 private slots:
    void onConfirmBtnClicked();

 private:
    Ui::ChooseMapToEdit ui;
    std::unique_ptr<EditingWindow> ew;
};

#endif  // CHOOSEMAPTOEDIT_H
