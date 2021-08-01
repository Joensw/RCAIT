#ifndef ABSTRACTGRAPHICSVIEW_H
#define ABSTRACTGRAPHICSVIEW_H

#include <QGraphicsItem>

class AbstractGraphicsView {
public:
    virtual void setAccuracyCurve(QGraphicsItem *accuracyCurveImage) {};

    virtual void setConfusionMatrix(QGraphicsItem *matrixImage) {};

    virtual void setTopAccuraciesGraphics(QGraphicsItem *topAccuraciesImage) {};

    virtual void setClassificationGraphics(QGraphicsItem *classificationGraphicsImage) {};

    [[nodiscard]] bool isSaved() const { return m_isSaved; };

    void setSaved(bool isSaved) { m_isSaved = isSaved; };

private:
    bool m_isSaved;
};

#endif // ABSTRACTGRAPHICSVIEW_H
