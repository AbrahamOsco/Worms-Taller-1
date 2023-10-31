#ifndef EDITINGWINDOW_H
#define EDITINGWINDOW_H

#include <QWidget>

namespace Ui {
class EditingWindow;
}

class EditingWindow : public QWidget
{
    Q_OBJECT

private slots:
    void onGoBackBtnClicked();

public:
    explicit EditingWindow(QWidget *parent = nullptr);
    void setPrev(QWidget* prev);
    void setLable(const std::string& text);
    ~EditingWindow();

private:
    Ui::EditingWindow *ui;
    QWidget *prev;
};

#endif // EDITINGWINDOW_H
