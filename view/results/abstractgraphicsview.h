#ifndef ABSTRACTGRAPHICSVIEW_H
#define ABSTRACTGRAPHICSVIEW_H

#include <QGraphicsItem>

class AbstractGraphicsView {
public:
    virtual void setLossCurve(QGraphicsItem *lossCurveImage) {};

    virtual void setConfusionMatrix(QGraphicsItem *matrixImage) {};
};

#endif // ABSTRACTGRAPHICSVIEW_H
