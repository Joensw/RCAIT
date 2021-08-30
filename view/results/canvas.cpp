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

[[maybe_unused]] bool Canvas::getAutoScale() const {
    return m_autoScale;
}

[[maybe_unused]] void Canvas::setAutoScale(bool autoScale) {
    m_autoScale = autoScale;
}
