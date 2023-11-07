#ifndef ZOOM_H
#define ZOOM_H

#include <QObject>
#include <QGraphicsView>

class Zoom : public QObject {
    Q_OBJECT
 public:
    explicit Zoom(QGraphicsView *view);

 private:
    QGraphicsView  *view;
    QPointF mousePosScene;
    QPointF mousePosView;
    bool eventFilter(QObject *watched, QEvent *event);

 signals:
    void zoomed();
};

#endif  // ZOOM_H
