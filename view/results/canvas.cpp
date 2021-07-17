#include <QGraphicsView>
#include "canvas.h"

Canvas::Canvas(bool autoScale) : QGraphicsView() {
    m_autoScale = autoScale;
    setAutoScale(m_autoScale);
}

void Canvas::setAutoScale(bool autoScale) {
    setHorizontalScrollBarPolicy(m_autoScale ? Qt::ScrollBarAlwaysOff : Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(m_autoScale ? Qt::ScrollBarAlwaysOff : Qt::ScrollBarAsNeeded);
}

void Canvas::paintEvent(QPaintEvent *pQEvent) {
    const QGraphicsScene *pQGScene = scene();
    if (pQGScene && m_autoScale) {
        fitInView(pQGScene->sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::paintEvent(pQEvent);
}

bool Canvas::autoScale() const {
    return m_autoScale;
}
