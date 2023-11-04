#include "zoom.h"
#include <QEvent>
#include <QWheelEvent>
#include <QtMath>

Zoom::Zoom(QGraphicsView *view):
    QObject(view),  view(view)
{
    view->viewport()->installEventFilter(this);
    view->setMouseTracking(true);
}

bool Zoom::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = (QMouseEvent*) event;
        QPointF delta = mousePosView - mouseEvent->pos();
        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
            mousePosView = mouseEvent->pos();
            mousePosScene = view->mapToScene(mouseEvent->pos());
        }
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = (QWheelEvent*) event;
        double angle = wheelEvent->angleDelta().y();
        double amount =  qPow(1.0015,angle);
        view->scale(amount,amount);
        view->centerOn(mousePosScene);
        QPointF deltaViewPos = mousePosView - QPointF(view->viewport()->width() / 2.0, view->viewport()->height() / 2.0);
        QPointF viewCenter = view->mapFromScene(mousePosScene) - deltaViewPos;
        view->centerOn(view->mapToScene(viewCenter.toPoint()));
        emit zoomed();
        return true;
    }
    Q_UNUSED(watched);
    return false;
}
