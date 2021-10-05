#include "canvas.h"

Canvas::Canvas(bool autoScale) :
        QGraphicsView(),
        m_autoScale(autoScale) {
}

/*!
\reimp
*/
void Canvas::paintEvent(QPaintEvent *paintEvent) {
    if (auto myscene = scene(); myscene && m_autoScale) {
        fitInView(myscene->sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::paintEvent(paintEvent);
}

[[maybe_unused]] bool Canvas::getAutoScale() const {
    return m_autoScale;
}

[[maybe_unused]] void Canvas::setAutoScale(bool autoScale) {
    m_autoScale = autoScale;
}
