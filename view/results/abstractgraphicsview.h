#ifndef ABSTRACTGRAPHICSVIEW_H
#define ABSTRACTGRAPHICSVIEW_H

#include <QGraphicsItem>

class AbstractGraphicsView {
public:
    virtual void setLossCurve(QGraphicsItem *lossCurveImage) {};

    virtual void setConfusionMatrix(QGraphicsItem *matrixImage) {};

    virtual void setTopAccuraciesGraphics(QGraphicsItem *topAccuraciesImage) {};

    virtual void setClassificationGraphics(QGraphicsItem *classificationGraphicsImage) {};
};

#endif // ABSTRACTGRAPHICSVIEW_H
