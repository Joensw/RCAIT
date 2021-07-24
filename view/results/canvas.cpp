#include <QGraphicsView>
#include "canvas.h"

Canvas::Canvas(bool autoScale) : QGraphicsView() {
    m_autoScale = autoScale;
}

void Canvas::paintEvent(QPaintEvent *pQEvent) {
    const QGraphicsScene *pQGScene = scene();
    if (pQGScene && m_autoScale) {
        fitInView(pQGScene->sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::paintEvent(pQEvent);
}

bool Canvas::getAutoScale() const {
    return m_autoScale;
}
