#include <QApplication>
#include "../include/editor.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyleSheet("QToolTip{color: #000000}");
    Editor w;
    w.show();
    return a.exec();
}
