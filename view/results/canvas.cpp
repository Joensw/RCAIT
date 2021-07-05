#include <QGraphicsView>
#include "canvas.h"

Canvas::Canvas(bool autoScale) : QGraphicsView() {
    setAutoScale(autoScale);
}

void Canvas::setAutoScale(bool autoScale) {
    mAutoScale = autoScale;
    setHorizontalScrollBarPolicy(mAutoScale ? Qt::ScrollBarAlwaysOff : Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(mAutoScale ? Qt::ScrollBarAlwaysOff : Qt::ScrollBarAsNeeded);
}

void Canvas::paintEvent(QPaintEvent *pQEvent) {
    const QGraphicsScene *pQGScene = scene();
    if (pQGScene && mAutoScale) {
        fitInView(pQGScene->sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::paintEvent(pQEvent);
}
