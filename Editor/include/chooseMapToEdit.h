#ifndef CHOOSEMAPTOEDIT_H
#define CHOOSEMAPTOEDIT_H

#include <QDialog>
#include "editingWindow.h"

namespace Ui {
class ChooseMapToEdit;
}

class ChooseMapToEdit : public QWidget {
    Q_OBJECT

 public:
    explicit ChooseMapToEdit(QWidget *parent = nullptr);
    void setPrev(QWidget* prev);
    ~ChooseMapToEdit();

 private slots:
    void onGoBackBtnClicked();
    void onConfirmBtnClicked();

 private:
    Ui::ChooseMapToEdit *ui;
    QWidget* prev;
};

#endif  // CHOOSEMAPTOEDIT_H
